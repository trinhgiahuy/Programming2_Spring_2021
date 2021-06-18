#include "library.hh"
#include <iostream>
#include<string.h>

// Let's use the date when the project was published as the first date.
Library::Library():
    today_(new Date(13, 11, 2019)),
    books_({}),
    authors_({}),
    accounts_({})
{

}

Library::~Library()
{
    // Free all memory reserved with the keyword new.
    delete today_; today_ = nullptr;
    for ( std::pair<std::string, Book*> book : books_ ){
        delete book.second;
        book.second = nullptr;
    }
    for ( std::pair<std::string, Person*> author : authors_ ){
        delete author.second;
        author.second = nullptr;
    }
    for ( std::pair<std::string, Person*> account : accounts_ ){
        delete account.second;
        account.second = nullptr;
    }
	for (std::pair<std::string, Loan*> loaning : loaning_data_) {
		delete loaning.second;
		loaning.second = nullptr;
	}
}

// Print all books in database
void Library::all_books()
{
    for ( std::pair<std::string, Book*> book : books_ ){
        std::cout << book.first << std::endl;
    }
}

// Print all books and info in database
void Library::all_books_with_info()
{
    std::cout << SEPARATOR_LINE << std::endl;
    for ( std::pair<std::string, Book*> book : books_ ){
        book.second->print_info();
        std::cout << SEPARATOR_LINE << std::endl;
    }
}

// Print all borrowers in database
void Library::all_borrowers()
{
    for ( std::pair<std::string, Person*> borrower : accounts_ ){
        std::cout << borrower.first << std::endl;
    }
}

// Print all borrowers and info in database
void Library::all_borrowers_with_info()
{
    std::cout << SEPARATOR_LINE << std::endl;
    for ( std::pair<std::string, Person*> borrower : accounts_ ){
        borrower.second->print_info();
        std::cout << SEPARATOR_LINE << std::endl;
    }
}


bool Library::add_book(const std::string &title, 
					   const std::vector<std::string> authors, 
					   const std::string &description, 
					   const std::set<std::string> genres)
{
    if ( authors.empty() ){
        std::cout << MISSING_AUTHOR_ERROR << std::endl;
        return false;
    }
    std::vector<Person*> author_ptrs;
    for ( std::string author : authors ){
        Person* n_person;
        if ( authors_.find(author) == authors_.end() ){
            n_person = new Person(author, "", "");
            authors_.insert({author, n_person});
        } else {
            n_person = authors_.at(author);
        }
        author_ptrs.push_back(n_person);
    }
    Book* n_book = new Book(title, author_ptrs, description, genres);
    books_.insert({title, n_book});
    return true;
}

// add new borrower to the database
void Library::add_borrower(const std::string &name, 
						   const std::string &email,
                           const std::string &address)
{
	// check if new borrower is already in the database
    if ( accounts_.find(name) != accounts_.end()){
        std::cout << DUPLICATE_PERSON_ERROR << std::endl;
        return;
    }

    Person* n_person = new Person(name, email, address);
    accounts_.insert({name, n_person});
}

// set new date to today
void Library::set_date(int day, int month, int year)
{
    delete today_;
    today_ = new Date(day, month, year);
    today_->show();
}

// go to a new day from today
void Library::advance_date(int days)
{
    today_->advance_by(days);
    today_->show();
}

/* Print all books which are borrowed
 * Returns:
 *  print all the books which are borrowed
 */
void Library::loaned_books()
{
	if (loaning_data_.begin() != loaning_data_.end()) {
		std::cout << LOAN_INFO << std::endl;
	}
	
	for (std::pair<std::string, Loan*> loaning_data : loaning_data_) {
		loaning_data.second->print_loaned(*today_);
	}
}

/* Print all books which are borrowed by a specific borrower
 * Parameters:
 *  borrower_id  name of person who borrows the book
 * Returns:
 *  print all the books which are borrowed by borrower_id
 */
void Library::loans_by(const std::string &borrower)
{
	// Check if the input borrower is in database
	if (accounts_.find(borrower) == accounts_.end()) {
		std::cout << CANT_FIND_ACCOUNT_ERROR << std::endl;
		return;
	}
	// Check every book in loaning data
	for (std::pair<std::string, Loan*> loaning_data : loaning_data_) {
		// If the book is loaned by the given person, print 
		if (loaning_data.second->getBorrower().compare(borrower) == 0) {
			loaning_data.second->print_loaned(*today_,false);
		}
	}
	
}

/* Loan a book to a borrower
 * Parameters:
 *  book_title   title of the book which is for loan
 *  borrower_id  name of person who borrows the book
 *
 */
void Library::loan(const std::string &book_title, 
				   const std::string &borrower_id)
{
	// Check if given book is in database
	if (books_.find(book_title) == books_.end()) {
		std::cout << CANT_FIND_BOOK_ERROR << std::endl;
		return;
	}
	// Check if given borrower is in database
	if (accounts_.find(borrower_id) == accounts_.end()) {
		std::cout << CANT_FIND_ACCOUNT_ERROR << std::endl;
		return;
	}
	// Check if given book is already in loaning data
	if (loaning_data_.find(book_title) != loaning_data_.end()) {
		std::cout << ALREADY_LOANED_ERROR << std::endl;
		return;
	}
	
	// create new due date start from today
	Date* n_due_date = 
		new Date(today_->getDay(),today_->getMonth(),today_->getYear());
	// advance from today to a period of loan time
	n_due_date->advance_by_loan_length();
	// add new loaning data
	Loan* n_loaning_data = 
		new Loan(books_.at(book_title), accounts_.at(borrower_id), n_due_date);
	loaning_data_.insert({ book_title, {n_loaning_data} });
}


/* Renew due date of a loaned book/ increase due date 
 *
 * Parameters:
 *  book_title   title of the loaned book whose due date is renewed
 *
 * Returns:
 *  print RENEWAL_SUCCESSFUL if the book is return successfully
 * 	print error if not
 */
void Library::renew_loan(const std::string &book_title)
{
	// Check if given book is in database
	if (books_.find(book_title) == books_.end()) {
		std::cout << CANT_FIND_BOOK_ERROR << std::endl;
		return;
	}
	// Check if given book is not already in loaning data
	if (loaning_data_.find(book_title) == loaning_data_.end()) {
		std::cout << LOAN_NOT_FOUND_ERROR << std::endl;
		return;
	}
	// Check if renewal is successful/ renewal times is not exceed MAX 
	// and increase due date to a default number of days
	if (loaning_data_.at(book_title)->advanceDueDate()) {
		std::cout << RENEWAL_SUCCESSFUL 
				  << loaning_data_.at(book_title)->getDueDate() 
				  << std::endl;
		return;
	}
	std::cout << OUT_OF_RENEWALS_ERROR << std::endl;

}

/* Remove a book from loaning data
 *
 * Parameters:
 *  book_title   title of the loaned book that is returned
 *
 * Returns:
 *  print RETURN_SUCCESSFUL if the book is return successfully
 * 	print error if not
 */
void Library::return_loan(const std::string &book_title)
{
	// Check if given book is in database
	if (books_.find(book_title) == books_.end()) {
		std::cout << CANT_FIND_BOOK_ERROR << std::endl;
		return;
	}
	// Check if given book is not in loaning data
	if (loaning_data_.find(book_title) == loaning_data_.end()) {
		std::cout << LOAN_NOT_FOUND_ERROR << std::endl;
		return;
	}
	// find loaned book that needs to be removed from loaning data
	std::map<std::string,Loan*>::iterator item_to_be_removed = 
												loaning_data_.find(book_title);
	// delete that book
	delete item_to_be_removed->second;
	item_to_be_removed->second = nullptr;
	loaning_data_.erase(item_to_be_removed);
	std::cout << RETURN_SUCCESSFUL << std::endl;
}
