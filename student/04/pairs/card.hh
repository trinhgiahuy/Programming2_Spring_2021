//
/* Class: Card
 * -----------
 * Represents a single card in pairs (memory) game.
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

#ifndef CARD_HH
#define CARD_HH

enum Visibility_type {OPEN, HIDDEN, EMPTY};
const char HIDDEN_CHAR = '#';
const char EMPTY_CHAR = '.';

class Card
{
public:
    // Oletusrakentaja: luo tyhjän kortin.
    //
    // Default constructor: creates an empty card.
    Card();

    // Rakentaja: luo piilotetun kortin, jonka kirjaimeksi tulee annettu merkki.
    //
    // Constructor: creates a hidden card with the given character.
    Card(const char c);

    // Ilmeiset setter- ja getter-metodit.
    //
    // Obvious setter and getter methods.
    void set_letter(const char c);
    void set_visibility(const Visibility_type visibility);
    char get_letter() const;
    Visibility_type get_visibility() const;


    // Turns a card: changes the visibility from open to hidden and vice versa.
    void turn();


    // Prints a card based on its current state (visibility).
    void print() const;


    // Removes a card from the game board: changes the visibility to empty.
    void remove_from_game_board();

private:
    char letter_;
    Visibility_type visibility_;
};

#endif // CARD_HH
