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
#include "player.hh"
#include <iostream>


Player::Player(const std::string& name):
name_(name)
{

}
// Add class implementation here.
// It should be enough to write only 1-2 code lines in each public method.

std::string Player::get_name() const
{
    return name_;
}

unsigned int Player::number_of_pairs() const
{
    return pairs_;
}

void Player::add_pair()
{
    pairs_ ++;
}

void Player::print() const
{
    std::cout <<"*** "<< name_ <<" has " << pairs_ <<" pair(s)."<< std::endl;
}

void Player::set_queu(int queu)
{
    queu_ = queu;
}

int Player::get_queu()
{
    return queu_;
}

void Player::add_card(Card &card)
{
    collected_cards.push_back(card);
}

