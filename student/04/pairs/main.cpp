/* Pairs
 *
 * Desc:
 *  This program generates a pairs (memory) game. The game has a variant
 * number of cards and players. At the beginning, the program also asks for a
 * seed value, since the cards will be set randomly in the game board.
 *  On each round, the player in turn gives the coordinates of two cards
 * (totally four numbers). After that the given cards will be turned as
 * visible and told if they are pairs or not. If they are pairs, they are
 * removed from the game board, the score of the player is increased, and
 * a new turn is given for the player. If the cards are not pairs, they
 * will be  turned hidden again, and the next player will be in turn.
 *  The program checks if the user-given coordinates are legal. The cards
 * determined by the coordinates must be found in the game board.
 *  After each change, the game board is printed again. The cards are
 * described as letters, starting from A and lasting so far as there are
 * cards. In printing the game board, a visible card is shown as its letter,
 * a hidden one as the number sign (#), and a removed one as a dot.
 *  Game will end when all pairs have been found, and the game board is
 * empty. The program tells who has/have won, i.e. collected most pairs.
 *
 * Program author 1
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
#include <player.hh>
#include <card.hh>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

const string INPUT_AMOUNT_OF_CARDS = "Enter the amount of cards (an even number): ";
const string INPUT_SEED = "Enter a seed value: ";
const string INPUT_AMOUNT_OF_PLAYERS = "Enter the amount of players (one or more): ";
const string INPUT_CARDS = "Enter two cards (x1, y1, x2, y2), or q to quit: ";
const string INVALID_CARD = "Invalid card.";
const string FOUND = "Pairs found.";
const string NOT_FOUND = "Pairs not found.";
const string GIVING_UP = "Why on earth you are giving up the game?";
const string GAME_OVER = "Game over!";

using Game_row_type = vector<Card>;
using Game_board_type = vector<vector<Card>>;

// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns 0
// (which leads to an invalid card later).
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}


// Fills the game board, the size of which is rows * columns, with empty cards.
void init_with_empties(Game_board_type& g_board, unsigned int rows, unsigned int columns)
{
    g_board.clear();
    Game_row_type row;
    for(unsigned int i = 0; i < columns; ++i)
    {
        Card card;
        row.push_back(card);
    }
    for(unsigned int i = 0; i < rows; ++i)
    {
        g_board.push_back(row);
    }
}


// Finds the next free position in the game board (g_board), starting from the
// given position start and continuing from the beginning if needed.
// (Called only by the function init_with_cards.)
unsigned int next_free(Game_board_type& g_board, unsigned int start)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    //
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Aloitetaan annetusta arvosta
    //
    // Starting from the given value
    for(unsigned int i = start; i < rows * columns; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY) // vaihdettu
        {
            return i;
        }
    }

    // Continuing from the beginning
    for(unsigned int i = 0; i < start; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY)
        {
            return i;
        }
    }

    // You should never reach this
    std::cout << "No more empty spaces" << std::endl;
    return rows * columns - 1;
}


// Initializes the given game board (g_board) with randomly generated cards,
// based on the given seed value.
void init_with_cards(Game_board_type& g_board, int seed)
{

    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();


    // Drawing a cell to be filled
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, rows * columns - 1);

    // Wiping out the first random number (that is always the lower bound of the distribution)
    distr(randomEng);


    // If the drawn cell is already filled with a card, next empty cell will be used.
    // (The next empty cell is searched for circularly, see function next_free.)
    for(unsigned int i = 0, c = 'A'; i < rows * columns - 1; i += 2, ++c)
    {

        // Adding two identical cards (pairs) in the game board
        for(unsigned int j = 0; j < 2; ++j)
        {
            unsigned int cell = distr(randomEng);
            cell = next_free(g_board, cell);
            g_board.at(cell / columns).at(cell % columns).set_letter(c);
            g_board.at(cell / columns).at(cell % columns).set_visibility(HIDDEN);
        }
    }
}


// Prints a line consisting of the given character c.
// The length of the line is given in the parameter line_length.
// (Called only by the function print.)
void print_line_with_char(char c, unsigned int line_length)
{
    for(unsigned int i = 0; i < line_length * 2 + 7; ++i)
    {
        cout << c;
    }
    cout << endl;
}


// Prints a variable-length game board with borders.
void print(const Game_board_type& g_board)
{

    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    print_line_with_char('=', columns);
    cout << "|   | ";
    for(unsigned int i = 0; i < columns; ++i)
    {
        cout << i + 1 << " ";
    }
    cout << "|" << endl;
    print_line_with_char('-', columns);
    for(unsigned int i = 0; i < rows; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < columns; ++j)
        {
            g_board.at(i).at(j).print();
            cout << " ";
        }
        cout << "|" << endl;
    }
    print_line_with_char('=', columns);
}


// Asks the desired product from the user, and calculates the factors of
// the product such that the factor as near to each other as possible.
void ask_product_and_calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor)
{
    unsigned int product = 0;
    while(not (product > 0 and product % 2 == 0))
    {
        std::cout << INPUT_AMOUNT_OF_CARDS;
        string product_str = "";
        std::getline(std::cin, product_str);
        product = stoi_with_check(product_str);
    }

    for(unsigned int i = 1; i * i <= product; ++i)
    {
        if(product % i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;
}


// More functions
/**
  * @brief the function split a string of input with space between them.
  * @return the vector of string that contain seperate substring.
  */
std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
        {
            std::string new_part = tmp.substr(0, tmp.find(delimiter));
            tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
            if(not (ignore_empty and new_part.empty()))
                {
                    result.push_back(new_part);
                }
        }
    if(not (ignore_empty and tmp.empty()))
         {
             result.push_back(tmp);
         }
    return result;
}

/**
  * @brief use to read player name and save to the existed list
  * @param list of player and player name string
  * @note Read a string of player name and push back it
  * into a vector
  */
void read_players_name(vector<Player>& players_list, std::string player_names)
{
    std::vector<std::string> player_name_list = split(player_names,' ', true);
    int num_player = player_name_list.size();
    for (int i=0; i < num_player; ++i)
    {
        players_list.push_back(Player(player_name_list.at(i)));
    }

}

/**
  * @brief use to read the given coordinate and check it validity
  * @param Class player
  * @return a string of input that included only given coordinate
  * @note it also consists case of quit command
  */
std::string check_cordinate_input(Player player)
{
    std::string cordinate_str = "";
    while (true)
    {
        std::cout << player.get_name()<<": "<< INPUT_CARDS ;
        getline(std::cin, cordinate_str);
        std::vector<std::string> cordinate_list = split(cordinate_str,' ', true);
        int cordinate_len = cordinate_list.size();
        for (int i = 0; i < cordinate_len; ++i)
        {

            //Check case alphabet input
            if (stoi_with_check(cordinate_list.at(i)) == 0 and cordinate_list.at(i) != "q")
            {
                std::cout<< INVALID_CARD << std::endl;
                break;
            }
            else
            {

                //Check quitting command
                if (i == 0 and cordinate_list.at(i) == "q")
                {
                    return cordinate_str;
                }
                else
                {
                    // check valid input
                    if (i == 3)
                    {
                        return cordinate_str;
                    }
                    continue;
                }
            }
        }
    }
}


/**
  * @brief covert the string cordinate to a vector<int> of coordinates
  * @param a string of valid coordinate
  * @return a vector of integer coordinate
  */
std::vector<int> cord_str_to_int(std::string coordinate_str)
{
    std::vector<std::string> coordinate_list = split(coordinate_str, ' ', true);
    std::vector<int> coordinate_int;
    int coordinate_list_len = coordinate_list.size();
    for (int i = 0; i < coordinate_list_len; ++ i)
    {
        coordinate_int.push_back(stoi_with_check(coordinate_list.at(i)));
    }
    return coordinate_int;
}


/**
  * @brief Check the validity of given coordinates
  * @param a vector of coordinate and a game board
  * @return true if coordinate is valid or false otherwise
  */
bool check_coordinate_valid(std::vector<int>& coord_vct,Game_board_type& g_board){

    int rows = g_board.size();
    int columns = g_board.at(0).size();
    int x1 = coord_vct.at(0);
    int y1 = coord_vct.at(1);
    int x2 = coord_vct.at(2);
    int y2 = coord_vct.at(3);

      // Case same coordinate input
      if (x1 == x2 && y1 == y2){
        std::cout<<INVALID_CARD<<std::endl;
        return false;
      }else{

        // Case coordinate run out of border input
        if (x1 < 1 || x1 > columns || x2 < 1 || x2 > columns || y1 < 1 || y1 > rows || y2 < 1 || y2 > rows ){
            //std::cout<<"6_"<<std::endl;
            std::cout<<INVALID_CARD<<std::endl;
            return false;
        }
        else
        {
            // because row and colummn transverse to each other
             Card Cell_1 = g_board.at(y1-1).at(x1-1);
             Card Cell_2 = g_board.at(y2-1).at(x2-1);

            // Case input coordinate = EMPTY
            if ( Cell_1.get_visibility() == EMPTY || Cell_2.get_visibility() == EMPTY){
                        std::cout<<INVALID_CARD<<std::endl;
                        return false;
             }
             else
             {
                //Coordinate valid
                    return true;
            }
         }
      }
}


/**
  * @brief  print the players information after printing the game_board
  * @param  A list of players
  */
void print_all_players_status(std::vector<Player> players_list)
{
    int player_list_len = players_list.size();

    for (int i = 0; i < player_list_len; ++i)
    {
        Player current_player = players_list.at(i);
        std::cout << "*** " << current_player.get_name() << " has " << current_player.number_of_pairs() << " pair(s)." << std::endl;
    }
}


/**
  * @brief  A function that control the game logic
  * @param  4 coordinates, a game board, list of players and a player class
  * @return true if player guess the pair or false if not
  * @note the coordiate parameter is input coordinate, not the board coordinate
  */
bool game_control(unsigned int x1,unsigned int y1, unsigned int x2, unsigned int y2,
                  Game_board_type& g_board, std::vector<Player>& players_list, Player& player){
        bool continue_turn;

        //Pass by reference to make a change to the board
        //The boardcoordinate equal to input coordinate minus 1
        // since the program value is from 0 and actual value is from 1.
        Card& Cell1 = g_board.at(y1-1).at(x1-1);
        Card& Cell2 = g_board.at(y2-1).at(x2-1);

        //Turn card of given coordinate
        Cell1.turn();
        Cell2.turn();
        print(g_board);

        if (Cell1.get_letter() != Cell2.get_letter()){
            std::cout<< NOT_FOUND<<std::endl;
            Cell1.turn();
            Cell2.turn();
            print_all_players_status(players_list);
            continue_turn = false;
        }
        else
        {
            player.add_card(Cell1);
            player.add_pair();
            Cell1.remove_from_game_board();
            Cell2.remove_from_game_board();
            std::cout<<FOUND<<std::endl;
            print_all_players_status(players_list);
            continue_turn = true;
        }
        print(g_board);

    return continue_turn;

}

/**
  * @brief  A function that check whether the game is over or not
  * @param  A game board
  * @return true if the game is over or false otherwise
  */
bool Game_is_over(Game_board_type g_board)
{
    int rows = g_board.size();
    int columns = g_board.at(0).size();
    int count_emty = 0;

    for (int i=0; i <rows; ++i)
    {
        for (int a=0; a<columns; ++a)
        {
            if (g_board.at(i).at(a).get_visibility() == EMPTY)
            {
                ++count_emty;
            }
        }
    }

    if (count_emty == (rows*columns))
    {
       return true;
    }
    return false;
}


/**
  * @brief  A function that find the largest number of pairs
  * that a player can have in a list of player
  * @param  A player list
  * @return the largest int number of pairs
  */
int find_largest_pairs(std::vector<Player> players_list)
{
    int players_list_len = players_list.size();
    unsigned int largest_pairs = 0;
    for (int i=0 ; i < players_list_len; ++i)
    {
        Player current_player = players_list.at(i);
        if (largest_pairs == 0)
        {
            largest_pairs = current_player.number_of_pairs();
        }
        else
        {
            if (current_player.number_of_pairs() > largest_pairs)
            {
                largest_pairs = current_player.number_of_pairs();

            }
        }
    }


    return largest_pairs;


}



/**
  * @brief  Determine if the game end with only 1 persion
  * or many multi tie players
  * @param  A player list
  */
void win_or_draw(std::vector<Player> players_list)
{
    int players_list_len = players_list.size();
    unsigned int largest_pairs = find_largest_pairs(players_list);
    int count_winners = 0;
    int winner_number = 0;

    for (int i = 0; i<players_list_len; ++i)
    {
        Player current_player = players_list.at(i);
        if (current_player.number_of_pairs() == largest_pairs)
        {
            // earse set_winner and get_winner if the following line is not needed
            //current_player.set_winner(true);
            winner_number = i;
            ++ count_winners;
        }
    }

    std::cout << GAME_OVER << std::endl;
    if (count_winners == 1)
    {
        std::cout << players_list.at(winner_number).get_name()
                  << " has won with " << largest_pairs << " pairs." << std::endl;
    }
    else if (count_winners > 1)
    {
        std::cout <<"Tie of " << count_winners << " players with "
                  << largest_pairs << " pairs." << std::endl;
    }
}



int main()
{
    Game_board_type game_board;

    unsigned int factor1 = 1;
    unsigned int factor2 = 1;
    ask_product_and_calculate_factors(factor1, factor2);
    init_with_empties(game_board, factor1, factor2);

    string seed_str = "";
    std::cout << INPUT_SEED;
    std::getline(std::cin, seed_str);
    int seed = stoi_with_check(seed_str);
    init_with_cards(game_board, seed);


    // More code
    int num_players = 0;

    while (num_players <= 0)
    {
        // read and check the amount of player
        std::cout<< INPUT_AMOUNT_OF_PLAYERS;
        string num_players_str = "";
        std::getline(std::cin,num_players_str);
        num_players = stoi_with_check(num_players_str);
    }

    // read players information
    std::cout << "List " << num_players << " players: ";
    std::string players_name;
    getline(std::cin, players_name);
    std::vector<Player> players_list;
    read_players_name(players_list,players_name);

    //print the initial board
    print(game_board);

    //Set queue number for each player equal to
    //their index in vector
    int players_list_len = players_list.size();
    for (int i = 0; i < players_list_len; i++){
        players_list.at(i).set_queu(i);
    }

    int turn = 0;
    //while loop control turn
    while (true)
    {
        for (int i = 0; i < num_players; ++i)
        {

            if (turn == num_players)
            {
                turn = 0;
            }
            else
            {
                if (players_list.at(i).get_queu() == turn)
                {
                        std::vector<int> coordinate_int;

                        //While loop control input
                        while(true){
                            std::string coordinate_str = check_cordinate_input(players_list.at(i));
                            if (coordinate_str == "q")
                            {
                                std::cout<<GIVING_UP<<std::endl;
                                return EXIT_SUCCESS;
                            }
                            coordinate_int = cord_str_to_int(coordinate_str);
                            bool is_valid_card = check_coordinate_valid(coordinate_int, game_board);
                            if (is_valid_card == true)
                            {
                                break;
                            }
                        }

                        int x1_coord = coordinate_int.at(0);
                        int x2_coord = coordinate_int.at(2);
                        int y1_coord = coordinate_int.at(1);
                        int y2_coord = coordinate_int.at(3);
                        bool continue_turn = game_control(x1_coord,y1_coord,x2_coord,y2_coord,game_board,
                                                          players_list,players_list.at(i));

                        if (Game_is_over(game_board))
                        {
                            win_or_draw(players_list);
                            return EXIT_SUCCESS;
                        }
                        else if (continue_turn == false)
                        {
                            turn++;
                            continue;
                        }
                }
              }
        }
    }
    return EXIT_SUCCESS;
}

