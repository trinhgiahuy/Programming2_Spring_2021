/*
 *  * Program author 1
 * Name: Trinh Gia Huy
 * Student number: H290290
 * UserID: bdgitr
 * E-Mail: giahuy.trinh@tuni.fi
 *
 * Program author 2
 * Name: Nguyen Nhat An
 * Student number: 050359099
 * UserID: kbanng
 * E-Mail: an.nguyen@tuni.fi
 * Notes about the program and it's implementation:
 *
 * */
#include "card.hh"
#include <iostream>

Card::Card():
    letter_(EMPTY_CHAR), visibility_(EMPTY)
{

}

Card::Card(const char c):
    letter_(c), visibility_(HIDDEN)
{

}

void Card::set_letter(const char c)
{
    letter_ = c;
}

void Card::set_visibility(const Visibility_type visibility)
{
    visibility_ = visibility;
}

char Card::get_letter() const
{
    return letter_;
}

Visibility_type Card::get_visibility() const
{
    return visibility_;
}

void Card::turn()
{
    if(visibility_ == HIDDEN)
    {
        visibility_ = OPEN;
    }
    else if(visibility_ == OPEN)
    {
        visibility_ = HIDDEN;
    }
    else // if(visibility_ == EMPTY)
    {
        std::cout << "Cannot turn an empty place." << std::endl;
    }
}

void Card::print() const
{
    // Kirjoita toteutus tähän
    // Write implementation here
}

void Card::remove_from_game_board()
{
    visibility_ = EMPTY;
}
