#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;

int main()
{
    string filename_input = "";

    cout << "Input file: ";
    getline(cin, filename_input);

    fstream file_in(filename_input);

    if (file_in)
    {
        map<string, set<int>> wordcount;

        int line_number = 1;
        string line = "";
        while (getline(file_in, line))
        {
            string::size_type i = 0;
            string::size_type space_position = 0;
            while (space_position != string::npos)
            {
                space_position = line.find(' ', i);
                string word = line.substr(i, space_position - i);
                if (wordcount.find(word) != wordcount.end())
                {
                    wordcount.at(word).insert(line_number);
                }
                else
                {
                    set<int> line_list = {line_number};
                    wordcount.insert({word, line_list});
                }

                i = space_position + 1;
            }


            line_number++;

        }

        for (auto data : wordcount)
        {
            cout << data.first << " " << data.second.size() << ": ";
            for (set<int>::iterator i = data.second.begin(); i != data.second.end(); i++)
            {
                if (i != data.second.begin())
                {
                    cout << ", ";
                }

                cout << *i;
            }

            cout << "\n";
        }
    }
    else
    {
        cout << "Error! The file " << filename_input << " cannot be opened.";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
