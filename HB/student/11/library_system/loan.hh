/* Module: Loan
 * ------------
 * This class and its bahaviour should be defined by the student.
 *
 * TIE-0220x S2019
 * */

// This header defines a class which is data types of a loan including
// loaned books, person who borrowed the book and due date of the loan
#ifndef LOAN_HH
#define LOAN_HH

#include "book.hh"
#include "date.hh"
#include "person.hh"

#include <string>
#include <vector>
#include <map>

class Person;

// Allowed renewal times, renewal will be failed if it is done more than this.
const int DEFAULT_RENEWAL_AMOUNT = 6;

class Loan
{
public:
	// Contructor of a loan data
	Loan(Book* loaned_book, Person* borrower, Date* due_date);
    ~Loan();

	// Return the person who borrowed the book
	std::string getBorrower() const;

	// Return due date of a loan
	std::string getDueDate() const;

	// increase due date when making a renewal
	// if renewal times exceeds above value, the renewal will fail
	bool advanceDueDate();

	// Print loan data, borrower can be printed or not, 
	// which depends on a bool input (true by default)
	void print_loaned(Date& rhs, bool borrower_print = true) const;
	
private:
	// Loan elements
	Book* loaned_book_;
	Person* book_borrower_;
	Date* due_date_;
	// renewal time is inialized as 0 for all loan
	unsigned int renewal_times_ = 0;
};

#endif // LOAN_HH
