#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;
const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


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

void print_a(string name, map<string, vector<string>> network, int count) {
    for(string i : network[name]){
        for (int j = 0; j < count; j++) {
            cout <<"..";
        }
        cout << i << endl;

        if (network[i].size() > 0) {
            int count2 = count + 1;
            print_a(i, network, count2);
        }
    }
    }


int print_b(string name, map<string, vector<string>> network, int count) {
    if (network[name].size() == 0) {
        return count+0;
    } else {
    for(string i : network[name]){
        count ++;
        count = print_b(i, network, count);
    }
        return count;
    }
}

int print_c(string name, map<string, vector<string>> network, int count) {
    if (network[name].size() == 0) {
        return count+1;
    } else {
        int f = 0;
        count ++;
        for(string i: network[name]){
            if (print_c(i, network, count) > f) {
                f = print_c(i ,network, count);
            }
        }
        count = f;
        return count;
    }
}

int main()
{
    // TODO: Implement the datastructure here
    map<string, vector<string>> network;



    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            network[id1].push_back(id2);

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            cout << id << endl;
            print_a(id, network, 1);

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

            cout << print_b(id, network, 0) << endl;

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

            cout << print_c(id, network, 0) << endl;

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
