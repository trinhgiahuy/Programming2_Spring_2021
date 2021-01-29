#ifndef BOOK_HH
#define BOOK_HH
#include "date.hh"
#include <iostream>
class Book
{
public:

  Book(std::string title, std::string author);
  ~Book();

  void print();

  void loan(Date date);

  void renew();

  void give_back();
  
private:
  std::string title_;
  std::string author_;

  bool available_ = true;

  Date loan_date_ ;
  Date return_date_ ;
};

#endif //BOOK_HH
