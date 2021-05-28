#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
    string filename_input = "";
    cout << "Input file: ";
    getline(cin, filename_input);

    ifstream file_in(filename_input);

    if (file_in)
    {
        map<string, int> player_point;
        string line = "";

        while (getline(file_in, line))
        {
            string::size_type colon_position = line.find(':');
            string name;
            name = line.substr(0, colon_position);
            int points;
            points = stoi(line.substr(colon_position + 1, line.length() - colon_position - 1));

            if (player_point.find(name) != player_point.end())
            {
                player_point.at(name) += points;
            } else
            {
                player_point.insert({name, points});
            }

        }

        file_in.close();

        cout << "Final scores:\n";
        for (auto data : player_point)
        {
            cout << data.first << ": " << data.second << "\n";
        }

    }
    else
    {
        cout << "Error! The file " << filename_input << " cannot be opened.";
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}
