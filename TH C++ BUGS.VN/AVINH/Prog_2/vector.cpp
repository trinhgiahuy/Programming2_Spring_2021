#include <iostream>
#include <vector>
#include <string>

using namespace std;

const char NORTH  = 'N';
const char EAST   = 'E';
const char SOUTH = 'S';
const char WEST = 'L';

void print_route(const vector<char>& routevector) {
    vector<char>::size_type index = 0;
    while ( index < routevector.size() ) {
        cout << routevector.at(index);
        ++index;
    }
    cout << endl;
}

int main() {
    string route = "";
    cout << "Input route: ";
    getline(cin, route);

    vector<char> optimized_route = { };
    string::size_type i = 0;
    while ( i < route.length() ) {
        char next_direction = route.at(i);

        if ( optimized_route.size() == 0 ) {
            optimized_route.push_back(next_direction);

        } else {
            char previous_direction = optimized_route.back();
            if ( previous_direction == EAST
                    and next_direction == WEST ) {
                optimized_route.pop_back();
            } else if ( previous_direction == WEST
                           and next_direction == EAST ) {
                optimized_route.pop_back();
            } else if ( previous_direction == NORTH
                           and next_direction == SOUTH ) {
                optimized_route.pop_back();
            } else if ( previous_direction == SOUTH
                           and next_direction == NORTH ) {
                optimized_route.pop_back();
            } else {
                optimized_route.push_back(next_direction);
            }
        }

        ++i;
    }
    print_route(optimized_route);
}