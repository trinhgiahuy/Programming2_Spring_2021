#include "book.hh"
#include "date.hh"
#include <iostream>

Book::Book(std::string title, std::string author):
  title_(title), author_(author){
    Date loan_date_(5,5,2020);
    Date return_date_(5,5,2020);
}

Book::~Book(){

}

void Book::print(){
  std::cout<<title_<<" : "<<author_<<std::endl; 
  if (available_){
    std::cout<<"- available"<<std::endl;
  }else{
    std::cout<<"- loaned: ";
    loan_date_.print();
    std::cout<<"- to be returned: ";
    return_date_.print();
  }
}

void Book::loan(Date date){
  if (!available_){
    std::cout<<"Already loaned: cannot be loaned"<<std::endl;
  }else{
    /// ??????????
    loan_date_ = date;
    return_date_ = date;
    return_date_.advance(28);
    available_ = false;
  }
}

void Book::renew(){
  if (available_){
    std::cout<<"Not loaned: cannot be renewed"<<std::endl;
  }else{
    return_date_.advance(28);
  }
}

void Book::give_back(){
  available_ = true;

  //delete loan_date_;
  //delete return_date_;
}

