#include <iostream>
#include <string>
#include <vector>

using namespace std;

// TODO: Implement split function here
// Do not change main function

std::vector <std::string> split(std::string line, char seperator, bool truth = false) {
    vector <std::string> result;
    int d = 0;
    int f = 0;
    bool flag;
    if ( truth == false ) {
        int a = 0;
        int b = 0;
        if (char(line[0]) == seperator) {
            flag = false;
        } else {
            flag = true;
        }
        for ( unsigned int i = 0; i < line.length(); i ++ ) {
            char c = char(line[i]);
            if (c == seperator) {
                if (flag == true) {
                    result.push_back(line.substr(a, b));
                    a += b;
                    b = 1;
                    f++;
                    flag = false;
                    d++;
                } else {
                    d++;
                    b++;
                }
            } else {
                if (flag == false) {
                    a += b;
                    b = 1;
                    flag = true;
                    if (d>2) {
                        for (int j = 1; j < d+1; j++) {
                            result.push_back("");
                        }
                    } else if (d == 2) {
                        result.push_back("");
                    }
                    d = 0;
                } else {
                    b ++;
                }
            }
        }
        if (char(line[line.length() - 1]) != seperator) {
            result.push_back(line.substr(a, b));
        } else if (d>2) {
            for (int j = 1; j < d+1; j++) {
                result.push_back("");
            }
        } else if (d == 2) {
            result.push_back("");
        }

    } else {
        int a = 0;
        int b = 0;
        bool flag;

        if (char(line[0]) == seperator) {
            flag = false;
        } else {
            flag = true;
        }

        for ( unsigned int i = 0; i < line.length(); i ++ ) {
            char c = char(line[i]);
            if (c == seperator) {
                if (flag == true) {
                    result.push_back(line.substr(a, b));
                    a += b;
                    b = 1;
                    flag = false;
                } else {
                    b++;
                }
            } else {
                if (flag == false) {
                    a += b;
                    b = 1;
                    flag = true;
                } else {
                    b ++;
                }
            }
        }

        if (char(line[line.length() - 1]) != seperator) {
            result.push_back(line.substr(a, b));
        } else if (d>2) {
                for (int j = 1; j < d+1; j++) {
                    result.push_back("");
                }
            } else if (d == 2) {
                result.push_back("");
            }
    }
        if ((int(line.length()) == 3) and (truth == false)) {
        result.push_back("");
    }
    return result;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }
    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
