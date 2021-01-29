#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit): owner_(owner), has_credit_(has_credit)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

int Account::get_balance(){
  return balance_;
}
void Account::save_money(signed int money){
  balance_ += money;
}

void Account::print() const{
  std::cout<<owner_<<" : "<<iban_<<" : "<<balance_<<" euros"<<std::endl;
}


void Account::set_credit_limit(signed int money){
  if (has_credit_){
    cre_limit_ = money;
  }else{
    std::cout<<"Cannot set credit limit: the account has no credit card"<<std::endl;
  }
}

void Account::take_money(signed int money){
  if (!has_credit_){
    if (money >  balance_){
      std::cout<<"Cannot take money: balance underflow"<<std::endl;
    }else{
      balance_ -= money;
      std::cout<<money<<" euros taken: new balance of "<<iban_<<" is "<<balance_<<" euros"<<std::endl;
    }
  }
  else{
    if (abs(balance_ - money) > cre_limit_){
      std::cout<<"Cannot take money: credit limit overflow"<<std::endl;
    }else{
      balance_ -= money;
      std::cout<<money<<" euros taken: new balance of "<<iban_<<" is "<<balance_<<" euros"<<std::endl;
    }
  }
}

void Account::transfer_to(Account& receiving_acc,signed int money){
  if (!has_credit_){
    if(money > balance_){
      std::cout<<"Cannot take money: balance underflow"<<std::endl;
      std::cout<<"Transfer from "<<iban_<<" failed"<<std::endl;
    }else{
      balance_ -= money;
      //receiving_acc.get_balance() += money;
      receiving_acc.save_money(money);
      std::cout<<money<<" euros taken: new balance of "<<iban_<<" is "<<balance_<<" euros"<<std::endl;
    }
  }else{
    if (abs(balance_ - money) > cre_limit_){
      std::cout<<"Cannot take money: credit limit overflow"<<std::endl;
      std::cout<<"Transfer from "<<iban_<<" failed"<<std::endl;
    }else{
      balance_ -= money;
      receiving_acc.save_money(money);
      std::cout<<money<<" euros taken: new balance of "<<iban_<<" is "<<balance_<<" euros"<<std::endl;
    }
  }
}


