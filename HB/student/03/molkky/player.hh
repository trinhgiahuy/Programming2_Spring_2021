#ifndef PLAYER_HH
#define PLAYER_HH

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;
class Player {
	public:
		Player(string name);
		string get_name() const;
		int get_points() const;
		void add_points(int points);
		bool has_won() const;
	private:
		string player_name_;
		int player_point_;
		bool state_;
};


#endif