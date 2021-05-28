#include "card.h"

// these are the cards of the matching game
Card::Card()
    : QPushButton()
{
    this->visibility_=EMPTY;
}


Card::Card(const QChar& text,QStack<Card*>* curclicked,
           QWidget* parent)
    : QPushButton(text,parent)
{
    this->curclicked = curclicked;
    this->setText("?");
    this->hiddentext=text;
    update();
}



Visibility_type Card::get_visibility()
{
    return visibility_;
}

void Card::setting(const QChar &text, QStack<Card*>* curclicked
                   )
{
    this->hiddentext.clear();
    this->curclicked = curclicked;
    this->setText("?");
    this->hiddentext =text;
}

// this slot reveals the text of the card when clicked
// if this is the first card that's been clicked, the revealed
// name stays on indefinitely. if it's the second card,
// both stay on for 0.5 seconds
void Card::reveal(){
    if (curclicked->empty()) {
        this->setText(hiddentext);
        update();
        curclicked->push(this);
    }
    else {
        this->setText(hiddentext);
        update();
        curclicked->push(this);
        emit checknow();
    }
}

// if a match happens, the button is disabled and text
// stays permanently on
void Card::matched() {
    this->setText(hiddentext);
    this->hide();
    this->setDisabled(true);
    this->visibility_ = EMPTY;
}
