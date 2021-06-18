// Implement all functions related to book loaning

#include "loan.hh"
#include <iostream>

// Iniallize a new loan
Loan::Loan(	Book* loaned_book,	Person* borrower,	Date* due_date):
	loaned_book_(loaned_book),book_borrower_(borrower),due_date_(due_date)
{

}

Loan::~Loan()
{
	
}

/* Get name of borrower as string
 * Return:
 *  name of the borrower
 */
std::string Loan::getBorrower() const
{
	return book_borrower_->get_name(); 
}

/* Get due date of a loan as string
 * Return:
 *  due date of the loan
 */
std::string Loan::getDueDate() const
{
	return due_date_->to_string();
}

/* Advance a due date if making a successful renewal
 * Return:
 *  True if the renewal is successful, false if not
 *
 */
bool Loan::advanceDueDate()
{
	//if renewal times not exceeds DEFAULT_RENEWAL_AMOUNT
	// do the renewal
	if (++renewal_times_ <= DEFAULT_RENEWAL_AMOUNT) {
		due_date_->advance_by_loan_length();
		return true;
	}
	return false;
}


/* Print loan data
 * Parameters:
 *  rhs   			today: for purpose of checking if the loan is late 
 *  borrower_print  whether to print the name of the borrower
 *
 */
void Loan::print_loaned(Date& rhs, bool borrower_print) const
{
	// print book that is loaned
	std::cout << loaned_book_->get_title() << " : ";

	// if needed to print the borrower's name
	if (borrower_print) {
		std::cout << book_borrower_->get_name() << " : ";
	}
	
	// Print due date of the loan
	std::cout << due_date_->to_string() << " : ";

	// if the due date was in the past, return "1" as "is late"
	if (due_date_->operator<(rhs)) {
		std::cout << "1" << std::endl;
	}
	else {
		std::cout << "0" << std::endl;
	}
}