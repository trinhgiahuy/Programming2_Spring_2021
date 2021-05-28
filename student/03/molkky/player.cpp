#include <iostream>
#include <string>
#include "player.hh"

using namespace std;

Player::Player(string name):
    name_(name), points_(0){
}

string Player::get_name() const
{
    return name_;
}

int Player::get_points() const
{
    return points_;
}

bool Player::has_won() const
{
    return (points_ == 50);
}

void Player::add_points(int points)
{
    if (points_ + points > 50)
    {
        cout << get_name() << " gets penalty points!\n";
        points_ = 25;
    }
    else
        points_ += points;
}

