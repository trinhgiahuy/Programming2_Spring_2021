#include "player.hh"

Player::Player(string name):
	player_name_(name),player_point_(0),state_(false) {
}

string Player::get_name() const{
	return player_name_;
}

int Player::get_points() const{
	return player_point_;
}

void Player::add_points(int points) {
	player_point_ += points;
	if (player_point_ > 50) {
	    player_point_ = 25;
	    cout << "Teppo gets penalty points!";
	    cout << endl;
	}
	if (player_point_ == 50) state_ = true;
	
}

bool Player::has_won() const{
    return (player_point_ == 50);
}
