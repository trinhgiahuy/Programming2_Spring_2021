/*  Source file for NumberTile class.
 *
 * Also contains an operator for pair addition.
 *
 * Method implementations should be added to the same level as the existing
 * ones.
 * */
#include "numbertile.hh"
#include <iomanip>
#include <iostream>

// Pair addition operator. Allows to do result_pair = pair_1 + pair_2
std::pair<int, int>operator +(std::pair<int, int> lhs, std::pair<int, int> rhs){
    return std::make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

// Modify the second line if you don't wish to use pairs.
NumberTile::NumberTile(int value,
                       std::pair<int, int> coords,
                       std::vector<std::vector<NumberTile> > *board)
    : value_(value)
{
    // Students should write their own implementation here, if necessary.


}

// Students should not touch this method.
void NumberTile::print(int width)
{
    // std::setw() sets the width of next printable to given amount, usually
    // by adding spaces in front.
    std::cout << "|" << std::setw(width - 1) << value_;
}

bool NumberTile::setValue(int value)
{
    // Students should write their own implementation here. Existing return
    // statement is allowed to be modified or removed.


    return true;
}


