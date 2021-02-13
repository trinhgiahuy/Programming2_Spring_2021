/* Class: Player
 * -------------
 * Represents a single player in pairs (memory) game.
 *
 * COMP.CS.110 K2021
 * */
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
#ifndef PLAYER_HH
#define PLAYER_HH

#include "card.hh"
#include <string>
#include <vector>

class Player
{
public:
    // Constructor: creates a player with the given name.
    Player(const std::string& name);

    // Returns the name of the player.
    std::string get_name() const;

    // Returns the number of pairs collected by the player so far.
    unsigned int number_of_pairs() const;

    // Increase 1 pair for player if each pair is correctly guess
    void add_pair();

    // Moves the given card from the game board for the player,
    // i.e. inserts it to the collected cards of the player and
    // removes it from the game board. Only one card of the pair is added
    void add_card(Card& card);

    // Prints the game status of the player: name and collected pairs so far.
    void print() const;

    // Return the queue number of player. The queue number is used for to change turn
    // of players in main function
    int get_queu();

    // Set the queue number for the player
    void set_queu(int queu);

private:
    std::string name_;
    int pairs_ = 0;
    std::vector<Card> collected_cards;
    int queu_;
};

#endif // PLAYER_HH
