#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

void Cards::reverse()
{
//    std::shared_ptr<Cards>new_card(new Cards);

//   Card_data* current = top_.get();
//    std::shared_ptr<Card_data> prev = nullptr;
//    Card_data* next = nullptr ;
//    while(current!=nullptr){
//        next = current->next.get();
//        current->next=prev;
//        prev.get()=current;
//    }
//    top_=prev;

        std::shared_ptr<Card_data> current = top_;
        std::shared_ptr<Card_data> prev = nullptr;
        std::shared_ptr<Card_data> next = nullptr ;
        while(current!=nullptr){
            next = current->next;
            current->next=prev;
            prev=current;
            current=next;
        }
        top_=prev;
}

bool Cards::remove(int &id)
{
    if ( top_ == nullptr ) {
            return false;
    }else{
    Card_data* card_remove = top_.get();
    id = card_remove->data;
    top_ = top_->next;
//    if (top_->data == bot_->data) {
//        top_ = nullptr;
//        bot_ = nullptr;
    }
    return true;
}


// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file reverse.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in reverse.cpp
