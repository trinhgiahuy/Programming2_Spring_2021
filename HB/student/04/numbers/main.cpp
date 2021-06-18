/* Numbers ( or 2048, but that's an invalid name ) : Template code
 *
 * Desc:
 *  This program generates a game of 2048, a tile combining game
 * where the goal is to get from 2's to 2048. The board is SIZE x SIZE,
 * ( original was 4x4 ) and every round the player chooses a direction
 * to which the tiles should fall. If they collide with a wall or a different
 * value, they will move as close as they can get. If they collide with
 * a tile with same value, they will combine and double the value. The
 * tile will continue to move until a wall or other tile comes along, but a
 * single tile can only be combined once per "turn".
 *  Game will end when the goal value asked (orig 2048) is reached or new
 * tile can't be added to the board.
 *
 * Program author ( Fill with your own info )
 * Name: Anh Huy Bui || Luu Tan Loc
 * Student number: 293257 || 281694
 * UserID: mfhubu || luul
 * E-Mail: huy.bui@tuni.fi || loc.luu@tuni.fi
 *
 * Notes about the program and it's implementation:
 * */

#include "numbertile.hh"
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <ctime>

const int SIZE = 4;
const int NEW_VALUE = 2;
const int PRINT_WIDTH = 5;
const int DEFAULT_GOAL = 2048;
const int DEFAULT_SEED = 1;

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

int goal_value = DEFAULT_GOAL;


enum class GameState { STOP, LOST, PLAYING, WON };
GameState CurrentState = GameState::PLAYING;

// Get value of box at (x, y)
int getBoxValue(const std::vector<std::vector<NumberTile>>& board, 
				std::size_t y, 
				std::size_t x) {
	return (board.at(x).at(y).getValue());
}

// Set value of box at (x, y)
void setBoxValue(std::vector<std::vector<NumberTile>>& board, 
				 std::size_t y,
				 std::size_t x,
				 int value) {
	(board.at(x).at(y).setValue(value));
}

// Scan every element of the board to chech if there are enough 
// numbers (count) of (find_value)
bool findValueInBoard(const std::vector<std::vector<NumberTile>>& board,
					  int find_value,
					  int count) {
	
	int found = 0;
	for (int x = 0; x < SIZE; x++) {
		for (int y = 0; y < SIZE; y++) {
			// one value that has been found
			if (getBoxValue(board, y, x) == find_value) found++; 
			if (found == count) return true; 
		}
	}
	return false;
}

// Adds new values to board using rEng and distr for random positioning.
void addNewValue(std::vector<std::vector<NumberTile>>& board,
				 std::default_random_engine& rEng,
				 std::uniform_int_distribution<int>& distr,
				 int HowMany) {
	// Tries to assign NEW_VAl to randomly selected tile. Continues trying until
	// newVal() returns true.

	// Check if there are enough 0 on the board 
	if (findValueInBoard(board, 0, HowMany)) { 
		int y = distr(rEng);
		int x = distr(rEng);
		int count = 0;
		// Continue until until the required number of new values are added
		while (count < HowMany) {	
			// New values are only added in replacement of 0
			if (getBoxValue(board, y, x) == 0) {	
				setBoxValue(board, y, x, NEW_VALUE);
				count++;
			}
			// continue getting random coordinates
			y = distr(rEng);
			x = distr(rEng);
		}
	}
}


// Prints the board.
void print(const std::vector<std::vector<NumberTile>>& board) {
	// The y isn't actually the y coordinate or some int, but an iterator that
	// is like a vector of NumberTiles.
	for (auto y : board) {
		// Prints a row of dashes.
		std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
		// And then print all cells in the desired width.
		for (auto x : y) {
			x.print(PRINT_WIDTH);
		}
		// And a line after each row.
		std::cout << "|" << std::endl;
	}
	// Print a last row of dashes so that the board looks complete.
	std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}

void setGoalValue() {
	std::cout << "Give a goal value or an empty line: ";
	std::string goal = "";
	getline(std::cin, goal);

	// check if the player has input a new goal value
	if (goal != "") {
		try {
			goal_value = stoi(goal);
		}
		catch (std::invalid_argument & ) {
			std::cout << "You have input wrong format of number. Goal value is set: " \
				      << goal_value << std::endl;
			return;
		}
	}
}

// Initializes the board to size SIZE x SIZE and adds SIZE tiles with NEW_VALUE
// to it through new_value() func after initializing the random engine with
// a seed value.
void initBoard(std::vector<std::vector<NumberTile>>& board,
			   std::default_random_engine& rEng,
			   std::uniform_int_distribution<int>& distr) {

	// Initialize the board with SIZE x SIZE empty numbertiles.
	for (auto y = 0; y < SIZE; y++) {
		board.push_back({});
		for (auto x = 0; x < SIZE; x++) {
			// If you don't want to use pairs, replace "std::make_pair(y, x)"
			// with "y, x".
			board.at(y).push_back(NumberTile(0));
		}

	}

	// Ask user for the seed value and initialize rEng.
	std::cout << "Give a seed value or an empty line: ";
	std::string seed = "";
	getline(std::cin, seed);

	if (seed == "") {
		// If the user did not give a seed value, use computer time as the seed
		// value.
		rEng.seed((int)time((time_t)NULL));
	}
	else {
		try {
			// If the user gave a seed value, use it.
			rEng.seed(stoi(seed));

		}
		catch (std::invalid_argument &) {
			rEng.seed(DEFAULT_SEED);
			std::cout << "You have input wrong format of number. Defaut seed is: " \
					  << DEFAULT_SEED << std::endl;
			return;
		}
	}

	// Add 4 new values to the blank board.
	addNewValue(board, rEng, distr, 4);
	setGoalValue();
}

// This function get values from a column or row of board and write to buffer
void readBoardAndWriteBuffer(const std::vector<std::vector<NumberTile>>& board, 
							 std::size_t u, 
							 std::vector<int>& buffer,
							 int direction) {
	
	for (auto t = 0; t < SIZE; t++) {
		switch (direction) {
		// Read value in one column, from (x,0) to (x,SIZE-1) 
		case UP:     
			// u, in this case, represents x
			if (getBoxValue(board, u, t) != 0)

				buffer.push_back(getBoxValue(board, u, t));
			break;
			
		// Read value in one column, from (x, SIZE-1) to (x, 0)
		case DOWN: 
			// u, in this case, represents x
			if (getBoxValue(board, u, (std::size_t) SIZE - 1 - t) != 0)
				buffer.push_back(getBoxValue(board, u, (std::size_t) SIZE - 1 - t));
			break;
			
		// Read value in one row, from (0, y) to (SIZE - 1, y)
		case LEFT:  
			// u, in this case, represents y while t represents x
			if (getBoxValue(board, t, u) != 0)
				buffer.push_back(getBoxValue(board, t, u));
			break;
					
		// Read value in one row, from (SIZE - 1 y) to (0, y)		
		case RIGHT:
			// u, in this case, represents y while t represents x
			if (getBoxValue(board, (std::size_t) SIZE - 1 - t, u) != 0)
				buffer.push_back(getBoxValue(board, (std::size_t) SIZE - 1 - t, u));
			break;
						
		default:
			break;
		}
		
	}
}

// This function will process the number in buffer with 2048's rules
void sortNumberInBuffer(std::vector<int>& buffer) {
	// Buffer contains value != 0, only sort when it has elements (not empty)
	if (buffer.size() > 0)	{ 
		for (std::size_t i = 0; i < buffer.size() - 1; i++) {
			// If there are 2 numbers in a row that have the same value 
			if (buffer.at(i) == buffer.at(i + 1)) { 
				// add the 2nd one to the 1st one
				buffer.at(i) += buffer.at(i + 1);	
				// remove the 2nd number
				buffer.erase(buffer.begin() + i + 1);
			}
		}
	}
}

// This function write values from buffer to board
void writeBuffer2Board(std::vector<std::vector<NumberTile>>& board, std::size_t u,
					   std::vector<int> buffer,
					   int direction) {

	for (std::size_t t = 0; t < SIZE; t++) {
		switch (direction) {
		// Write buffer to column from (x,0) to (x,SIZE - 1)
		case UP: 
			// u represents x, t represents y
			if (t < buffer.size())
				setBoxValue(board, u, t, buffer.at(t));
			// missing values will be written  0
			else setBoxValue(board, u, t, 0);
			break;
			
		// Write buffer to column from (x,SIZE - 1) to (x,0)
		case DOWN: 

			// u represents x, SIZE - 1 - t represents y
			if (t < buffer.size())
				setBoxValue(board, u, (std::size_t) SIZE - 1 - t, buffer.at(t));
			// missing values will be written  0
			else setBoxValue(board, u, (std::size_t) SIZE - 1 - t, 0);
			break;

		// Write buffer to row from (0,y) to (SIZE - 1,y)
		case LEFT: 
			// t represents x, u represents y
			if (t < buffer.size())
				setBoxValue(board, t, u, buffer.at(t));
			// missing values will be written  0
			else setBoxValue(board, t, u, 0);
			break;

		// Write buffer to row from (SIZE - 1,y) to (0,y)
		case RIGHT: 
			// SIZE - 1 - t represents x, u represents y
			if (t < buffer.size())
				setBoxValue(board, (std::size_t) SIZE - 1 - t, u, buffer.at(t));
			// missing values will be written  0
			else setBoxValue(board, (std::size_t) SIZE - 1 - t, u, 0);
			break;

		default:
			break;
		}
	}
}

// This function check if there is any posible move that can be made
bool checkIsTherePossibleMove(const std::vector<std::vector<NumberTile>>& board) {
	// It is necessary only when there is no 0 in the board
	if (!findValueInBoard(board, 0, 1)) { 
		for (std::size_t u = 0; u < (std::size_t) SIZE - 1; u += (std::size_t) 1) { 
			for (std::size_t v = 0; v < (std::size_t) SIZE; v += (std::size_t) 1) {
				// Check if there are 2 adjacent numbers on the same column that are equal 
				if (getBoxValue(board, u, v) == getBoxValue(board, u + 1, v) || 
				// Check if there are 2 adjacent numbers on the same row that are equal
					getBoxValue(board, v, u) == getBoxValue(board, v, u + 1))
					return true;
			}
		}
		return false;
	}
	else return true;
}

//	After player has taken the move, this function will decide what to do next.
void endCommand(std::vector<std::vector<NumberTile>>& board,
				std::default_random_engine& rEng,
				std::uniform_int_distribution<int>& distr) {


	if (findValueInBoard(board, goal_value, 1)) {
		// scan the board and find 1 value that reached goal value
		CurrentState = GameState::WON;
		std::cout << "You reached the goal value of " << goal_value << std::endl;
		print(board);
		return;
	}
	// no goal value is found. Add a new number
	addNewValue(board, rEng, distr, 1);
	print(board);

	// After a new number is added, check whether the player is still able 
	// to take the move. If no, the player lost the game
	if (!checkIsTherePossibleMove(board)) {
		CurrentState = GameState::LOST;
		std::cout << "Can't add new tile, you lost!";
		return;
	}
}

// 1. Move command: Collect numbers from 1 column or row from up/down/left/right
// to down/up/right/left depend on direction.
// 2. Sort the colleccted numbers
// 3. Rewrite to the board
void inputCommand(std::vector<std::vector<NumberTile>>& board,
				  std::default_random_engine& rEng,
				  std::uniform_int_distribution<int>& distr,
				  int direction) {
	
	std::vector<int> buffer;
	// Init u as coordinate (x or y) depends on direction (row or column)
	for (std::size_t u = 0; u < SIZE; u++) {
		//Collect the numbers from the board and write to a buffer
		readBoardAndWriteBuffer(board, u, buffer, direction); 
		sortNumberInBuffer(buffer); 
		writeBuffer2Board(board, u, buffer, direction);
		//Empty buffer and go to next row/ collumn
		buffer.clear();
	}
	endCommand(board, rEng, distr); // Check WIN/LOSE or ADD a new number
}


int main()
{
	// Declare the board and randomengine.
	std::vector<std::vector<NumberTile>> board;
	std::default_random_engine randomEng;
	// And initialize the disrt to give numbers from the correct
	std::uniform_int_distribution<int> distr(0, SIZE - 1);
	initBoard(board, randomEng, distr);
	print(board);
	// if the current state is still in "Playing"
	while (CurrentState == GameState::PLAYING) {
		std::cout << "Dir> ";
		char dir;
		// Get player's command
		std::cin >> dir; 
		switch (dir) {
			case 'w':
				inputCommand(board, randomEng, distr, UP);
				break;
			case 's':
				inputCommand(board, randomEng, distr, DOWN);
				break;
			case 'a':
				inputCommand(board, randomEng, distr, LEFT);
				break;
			case 'd':
				inputCommand(board, randomEng, distr, RIGHT);
				break;
			case 'q':
				// Quit - Stop the game. Current state changes to stop.
				CurrentState = GameState::STOP;
				/// std::cout << "Game end!" << std::endl;
				return 0;
			default:
				std::cout << "Error: unknown command." << std::endl;
				break;
		}
	}
}
