#include "cards.hh"

// TODO: Implement the methods here
Cards::Cards():top_(nullptr),bot_(nullptr){}


void Cards::add(int id)
{
    Card_data* new_card=new Card_data{id,nullptr};
    if(top_==nullptr){

        top_=new_card;
        bot_=new_card;
    }else{
        new_card->next = top_;
        top_= new_card;
    }
}

void Cards::print_from_top_to_bottom(std::ostream &s){
    int i=1;
    Card_data* iter;
    iter=top_;
    while(iter!=nullptr){
        s<<i<<": "<<iter->data<<std::endl;
        iter=iter->next;
        i++;
    }
}

bool Cards::bottom_to_top(){
    if(top_==nullptr){
        return false;
    }
    Card_data* count;
    count=top_;
    Card_data* new_card= new Card_data;
    new_card->data=bot_->data;
    new_card->next=top_;
    top_=new_card;

    while (count!=nullptr) {
        if(count->next==bot_){
            count->next=nullptr;
            bot_=count;
            break;
        }else{
            count=count->next;
        }
    }

    return true;
}

bool Cards::top_to_bottom(){
    if(top_==nullptr){
        return false;
    }
    Card_data* new_card=new Card_data;
    new_card->data=top_->data;
    bot_->next=new_card;
    bot_=new_card;
    top_=top_->next;
    return true;

}

void Cards::print_from_bottom_to_top(std::ostream &s){
    Card_data* top_ptr=nullptr;
//    top_ptr=top_;
    Card_data* bot_ptr=bot_;
    int i =1;

    while (bot_ptr!=top_) {

        s<<i<<": "<<bot_ptr->data<<std::endl;

        top_ptr=top_;
        i++;
        while(top_ptr!=nullptr){
            if(top_ptr->next==bot_ptr){
                  bot_ptr=top_ptr;
            }else{
             top_ptr=top_ptr->next;
            }

        }
    }

    s<<i<<": "<<top_->data<<std::endl;
}

bool Cards::remove(int &id) {
    if ( top_ == nullptr ) {
        return false;
    }

    Card_data* card_remove = top_;

    id = card_remove->data;

    if (top_->data == bot_->data) {
        top_ = nullptr;
        bot_ = nullptr;
    } else {
        top_ = top_->next;
    }

    delete card_remove;

    return true;
}

Cards::~Cards(){
    while(top_!=nullptr){
        top_=top_->next;
    }
}
