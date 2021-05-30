/* Program author 1
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
 * Desc:
 * a program that first reads information concerning tramways from the input file,
 * stores them into a suitable data structure, and then permits the user to make searches,
 * insertions, and removals in the data structure in question.
 * */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    std::cout <<
                 "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------" << std::endl;
}



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
  * @brief the function take each line from given input file and add it
  * to a data struct and handle special case input
  * @return false if its format in file is not valid and true if successfuly
  */
bool input_to_copy_rasse(std::string line,
                         std::map<std::string,std::vector<std::vector<std::string>>>& copy_rasse_line_map)
{

    //format of line_vct = {line,stop,distance}
    std::vector<std::string> line_vct = split(line,';');
    if (line_vct.size() != 2 and line_vct.size() != 3)
    {
        std::cout<<"Error: Invalid format in file." << std::endl;
        return false;
    }
    else
    {
        if (line_vct.size() == 3 and line_vct.at(2) != "" )
        {
            copy_rasse_line_map[line_vct.at(0)].push_back({line_vct.at(1), line_vct.at(2)});
        }
        else
        {
            copy_rasse_line_map[line_vct.at(0)].push_back({line_vct.at(1), "0"});
        }

    }

    return true;
}



/**
  * @brief the function handling of case stop/line already exist.
  * @param the data structure that store all information about line/stop and their distance
  * @return the false if the error encounter and true if not.
  */
bool stop_distance_error_handling(std::map<std::string,std::vector<std::vector<std::string>>> copy_rasse_line_map)
{

    for (auto i = copy_rasse_line_map.begin(); i != copy_rasse_line_map.end(); i++)
    {
        std::vector<std::vector<std::string>> check_list = i->second;
        std::sort(check_list.begin(), check_list.end());
        for (unsigned int a=0; a < check_list.size()-1; a++)
        {
            //same STOP error
            std::string current_stop = check_list.at(a).at(0);
            std::string next_stop = check_list.at(a+1).at(0);
            if (current_stop == next_stop)
             {
                 std::cout << "Error: Stop/line already exists." << std::endl;
                 return false;
             }
            //same DISTANCE error
            for (unsigned int j = a+1; j < check_list.size(); j++)
            {
                std::string current_distance = check_list.at(a).at(1);
                std::string next_distance = check_list.at(j).at(1);
                if (current_distance == next_distance)
                {
                    std::cout << "Error: Stop/line already exists." << std::endl;
                    return false;
                }
            }
         }
      }
    return true;
}



/**
  * @brief the function add the coppied data structure into the main data structures.
  * @param 2 main data structures and the copied data structure
  * @note we will use copied data structure for handling initilize error.
  */
void add_into_main_map( std::map<std::string,std::vector<std::vector<std::string>>> copy_rasse_line_map,
                        std::map<std::string,std::map<std::string, float>>& rasse_line_map,
                        std::map<std::string,std::vector<std::string>>& rasse_stop_map)
{

    for (auto i = copy_rasse_line_map.begin(); i != copy_rasse_line_map.end(); i++)
    {
        std::vector<std::vector<std::string>> check_list = i->second;
        for (unsigned int a=0; a<check_list.size(); a++)
        {

            std::string stop = check_list.at(a).at(0);
            std::string line = i->first;
            float distance = std::stof(check_list.at(a).at(1));

            //add into map line

            rasse_line_map[line][stop] = distance;

            //add into map stop
            unsigned int map_len = rasse_stop_map.size();
            if (map_len != 0 and rasse_stop_map.find(stop) != rasse_stop_map.end())
            {
                rasse_stop_map[stop].push_back(line);
            }
            else
            {
                rasse_stop_map[stop] = {line};
            }
        }
    }
}



/**
  * @brief the function will take of multi-words name string that is splited by white space
  * and return a completed multi-words name string
  * @param a list of vector of string that is split by white space and starting index
  * @return a complete string name.
  * @note Can be used normal for single-word name string.
  * For example : take name such as "Hervannan Kampus A", "Hervannan Kampus B",...
  */
std::string take_multi_name(std::vector<std::string> use_vector, int start_index)
{
    std::string stop_name;
    std::string first_name = use_vector.at(start_index);
    unsigned int use_vector_len = use_vector.size();
    unsigned int first_name_len = first_name.size();


    // STOP "Hervannan Campus"
    if (first_name.at(0) == '"')
    {
        if (first_name.back() == '"')
        {
            stop_name = first_name.substr(1, first_name_len-2);
        }
        else
        {
            stop_name = first_name.substr(1, first_name_len-1);
            // check for the name "Hervanan A Campus"
            for (unsigned int i = start_index+1; i < use_vector_len; i++)
            {

                std::string current_name = use_vector.at(i);
                if (current_name.back() == '"')
                {
                    stop_name += ' ' + current_name.substr(0, current_name.size()-1);
                    break;
                }
                else
                {
                    stop_name += ' ' + current_name;
                }
            }
        }
    }
    else
    {
        stop_name = first_name;
    }

    return stop_name;
}



/**
  * @brief the function help to print out the lines that sorted by its distance value
  * @param a small main data structure and line name string
  * @note use data struct pair<float,string> to sort and print out the lines
  *
  *
  */
void print_line(std::map<std::string,std::map<std::string, float>> line_map,
                std::string line_name)
{

    std::vector<std::pair<float,std::string>> distances_stops;
    for (auto i = line_map[line_name].begin(); i!= line_map[line_name].end(); i++)
    {
        // i-> first is stopm i->second is distance
        distances_stops.push_back({i->second, i->first});
    }
    std::sort(distances_stops.begin(), distances_stops.end());
    for (unsigned int a = 0; a < distances_stops.size(); a++)
    {
        std::cout << "- " << distances_stops.at(a).second << " : " << distances_stops.at(a).first<< std::endl;
    }

}



/**
  * @brief function that execute the command "LINE" that will print out the line_name and
  * all stops that it goes through.
  * @param main large data structure and the vector contain strings of comand parameters.
  * @note in case the line do not have any stop it still print the message go through.
  */
void line_command(std::map<std::string,std::map<std::string, float>> line_map,
                  std::vector<std::string> use_vector)
{

    unsigned int use_vector_len = use_vector.size();
    if (use_vector_len == 1)
    {
        std::cout << "Error: Invalid input." << std::endl;
    }

    else
    {
          std::string line_name = take_multi_name(use_vector, 1);
          if (line_map.find(line_name) == line_map.end())
            {
              std::cout << "Error: Line could not be found." << std::endl;
            }
          else
            {
                std::cout << "Line " << line_name
                << " goes through these stops in the order they are listed:" << std::endl;
                std::map<std::string, float> stop_distance = line_map[line_name];
                // case line have stop
                if (!stop_distance.empty())
                {
                   print_line(line_map, line_name);

                }
            }
    }
}



/**
  * @brief function that execute the command "STOP" that will print out the stop_name and
  * all lines that it goes through.
  * @param main small data structure and the vector contain strings of comand parameters.
  */
void stop_command(std::map<std::string,std::vector<std::string>> rasse_stop_map, std::vector<std::string> use_vector)
{
    unsigned int use_vector_len = use_vector.size();
    if (use_vector_len == 1)
    {
        std::cout << "Error: Invalid input." << std::endl;
    }
    else
    {
        std::string stop_name = take_multi_name(use_vector, 1);

        if (rasse_stop_map.find(stop_name) == rasse_stop_map.end())
        {
            std::cout << "Error: Stop could not be found." << std::endl;
        }
        else
        {
            std::cout << "Stop " << stop_name << " can be found on the following lines:" << std::endl;
            unsigned int lines = rasse_stop_map[stop_name].size();
            if (lines != 0)
            {
                for (unsigned int i = 0; i < lines; i++)
                {
                    std::string current_line = rasse_stop_map[stop_name].at(i);
                    std::cout << "- " << current_line << std::endl;
                }
            }

        }
    }
}



/**
  * @brief calculate the distance between 2 stops of the same line
  * @param a main large data structure and the vector contain strings of comand parameters.
  * @note the function also handle all cases of multi-words stop/line names
  */
void distance (std::map<std::string,std::map<std::string, float>>& map_line,
               std::vector<std::string> use_vector)
{
    // Case of only command input without parameter.
    unsigned int use_vector_len = use_vector.size();
    if (use_vector_len == 1)
    {
        std::cout<<"Error: Invalid input."<<std::endl;
        return;
    }

    std::string line = take_multi_name(use_vector,1);
    unsigned int first_new_index = split( line , ' ').size()+1;

    if (first_new_index < use_vector_len )
    {

        std::string first_stop  = take_multi_name(use_vector,first_new_index);
        unsigned int second_new_index = split(first_stop,' ').size()+first_new_index;


        if (second_new_index < use_vector_len )
        {

           std::string second_stop = take_multi_name(use_vector,second_new_index) ;
            //unsigned int third_new_index = split(second_stop,' ').size()+second_new_index;
            if(map_line.find(line) == map_line.end())
            {
                std::cout<<"Error: Line could not be found."<<std::endl;
            }
            else
            {
                std::map<std::string, float>temp_map = map_line[line];
                if (temp_map.find(first_stop) == temp_map.end() || temp_map.find(second_stop) == temp_map.end())
                {
                    std::cout<<"Error: Stop could not be found."<<std::endl;
                }
                else
                {
                    float first_dist = temp_map[first_stop];
                    float  second_dist = temp_map[second_stop];
                    float dist_diff = 0.0;

                    if (first_dist >= second_dist)
                    {
                        dist_diff = first_dist - second_dist;
                    }
                    else
                    {
                        dist_diff = second_dist -first_dist;
                    }
                    std::cout<<"Distance between "<<first_stop<<" and "<<second_stop<<" is "<<dist_diff<<std::endl;
                }
            }
        }
        else
        {
            std::cout<< "Error: Invalid input." << std::endl;
        }
    }
    else
    {
        std::cout<< "Error: Invalid input." << std::endl;
    }
}



/**
  * @brief add line into the data structure
  * @param a small main data structure and the vector contain strings of comand parameters.
  * @note the function also add multi-words line names
  */
void add_line(std::map<std::string,std::map<std::string, float>>& map_line,
              std::vector<std::string> use_vector)
{
    if (use_vector.size() < 2)
    {
        std::cout<<"Error: Invalid input." << std::endl;
    }
    else
    {
        std::string line  = take_multi_name(use_vector,1);

        //Error case line already exist
        if ( map_line.find(line) != map_line.end())
        {
            std::cout<<"Error: Stop/line already exists."<<std::endl;
        }
        else
        {
            //Implement an empty map for the added line
            std::map<std::string,float>empty_map;
            map_line.insert({line,empty_map});
            std::cout<<"Line was added."<<std::endl;
        }
    }
}



/**
  * @brief A function check that if a given string is number or alphabet words
  * @param A tested string
  * @return True if it is a number and false if not
  * @note The function take into both float number and integer cases
  */
bool isNumber(std::string s)
{
    std::size_t char_pos(0);

    // skip the whilespaces
    char_pos = s.find_first_not_of(' ');
    if (char_pos == s.size())
        return false;

    // check the significand
    if (s[char_pos] == '+' || s[char_pos] == '-')
        ++char_pos; // skip the sign if exist

    int n_nm, n_pt;
    for (n_nm = 0, n_pt = 0; std::isdigit(s[char_pos]) || s[char_pos] == '.'; ++char_pos)
    {
        s[char_pos] == '.' ? ++n_pt : ++n_nm;
    }
    if (n_pt>1 || n_nm<1) // no more than one point, at least one digit
        return false;

    // skip the trailing whitespaces
    while (s[char_pos] == ' ')
    {
        ++ char_pos;
    }

    return char_pos == s.size();  // must reach the ending 0 of the string
}



/**
  * @brief add stop into the data structure and execute the commnad "ADDSTOP"
  * @param both main data structure and the vector contain strings of comand parameters.
  * @note the function handle all multi-words line/stop name cases
  */
void add_stop(std::map<std::string,std::map<std::string, float>>& map_line,
              std::map<std::string,std::vector<std::string>>& map_stop,
              std::vector<std::string> use_vector
              )
{
    unsigned int use_vector_len = use_vector.size();
    if(use_vector_len == 1)
    {
        std::cout<<"Error: Invalid input."<<std::endl;
        return;
    }
    std::string line = take_multi_name(use_vector,1);
    unsigned int first_new_index = split( line , ' ').size()+1;


    //Case 1 parameter case (single and multi name)
    if (first_new_index < use_vector_len && use_vector_len >= 4)
    {
        std::string stop  = take_multi_name(use_vector,first_new_index);
        unsigned int second_new_index = split(stop,' ').size()+first_new_index;

        if (use_vector_len < 4 || second_new_index >= use_vector_len)
        {
            std::cout << "Error: Invalid input." << std::endl;
        }
        else
        {
            float dist = stof(use_vector.at(second_new_index));
            //Error line unknown case
            if (map_line.find(line) == map_line.end())
            {
                std::cout<<"Error: Line could not be found."<<std::endl;
            }
            else
            {
                std::map<std::string,float> copied_temp_stop_map;
                std::map<std::string,float>::iterator ite;
                copied_temp_stop_map = map_line[line];
                bool stop_is_exist = false;


                for(ite = copied_temp_stop_map.begin();
                    ite != copied_temp_stop_map.end(); ite++)
                {
                    //std::cout<<ite->first<<" "<<ite->second<<std::endl;
                    if (ite->first == stop || ite->second == dist)
                    {
                        //Error case stop already exist
                        std::cout<<"Error: Stop/line already exists."<<std::endl;
                        stop_is_exist = true;
                        break;
                    }
                }

                if (!stop_is_exist){
                    std::map<std::string,float> temp_stop_map;

                    //Insert map_stop (A small main data struct)
                    std::vector<std::string> temp_line_vector;
                    temp_line_vector.push_back(line);
                    map_stop[stop]=temp_line_vector;

                    //Insert map_line (A large main data struct)
                    map_line[line][stop] = dist;
                    std::cout<<"Stop was added."<<std::endl;
                }
            }
        }
    }
    else
    {
        //std::cout << "??"<<std::endl;
        std::cout << "Error: Invalid input." << std::endl;
    }
}



/**
  * @brief remove the stop the data structure and execute the commnad "REMOVE"
  * @param both main data structure and the vector contain strings of comand parameters.
  * @note the function handle all multi-words stop name cases
  */
void remove_command(std::map<std::string,std::map<std::string, float>>& rasse_line_map,
                    std::map<std::string,std::vector<std::string>>& rasse_stop_map,
                    std::vector<std::string> use_vector)
{
    unsigned int use_vector_len = use_vector.size();
    if (use_vector_len == 1)
    {
        std::cout << "Error: Invalid input." << std::endl;
    }
    else
    {
        std::string stop_name = take_multi_name(use_vector, 1);
        if (rasse_stop_map.find(stop_name) == rasse_stop_map.end())
        {
            std::cout << "Error: Stop could not be found." << std::endl;
        }
        else
        {
            rasse_stop_map.erase(stop_name);
            for (auto i = rasse_line_map.begin(); i != rasse_line_map.end(); i++)
            {
                //i->second is a map that has key of stop and value of distance;
                if (i->second.find(stop_name) != i->second.end())
                {
                    //std::cout << "===" << std::endl;
                    //if can find
                    i->second.erase(stop_name);
                }
            }

            std::cout<< "Stop was removed from all lines." << std::endl;
        }
    }
}



// Short and sweet main.

int main()
{
    print_rasse();

    std::map<std::string,std::map<std::string, float>> rasse_line_map;
    std::map<std::string,std::vector<std::string>> rasse_stop_map;
    std:: string filename = "";
    std::cout << "Give a name for input file: ";
    getline(std::cin,filename);
    // process input error
    std::ifstream file_object(filename);


        if ( not file_object )
        {
            std::cout << "Error: File could not be read." << std::endl;
            return EXIT_FAILURE;
        }
        else
        {

            std::string line;
            std::map<std::string,std::vector<std::vector<std::string>>> copy_rasse_line_map;
            while (getline(file_object, line))
            {
                if (!input_to_copy_rasse(line, copy_rasse_line_map))
                {
                    return EXIT_FAILURE;
                }
            }

            if (!stop_distance_error_handling(copy_rasse_line_map))
            {
                return EXIT_FAILURE;
            }
            add_into_main_map(copy_rasse_line_map, rasse_line_map, rasse_stop_map);
        }


        //main_function
        while (true)
        {
            std::string user_input;
            std::cout << "tramway> ";
            getline(std::cin, user_input);
            std::vector<std::string> user_vector = split(user_input, ' ');
            std::vector<std::string> use_vector;
            int input_len = user_vector.size();

            if (input_len > 0)
            {
                //take data that will be used

                for (int i=0; i<input_len; i++)
                {
                    use_vector.push_back(user_vector.at(i));
                }


                // ADDSTOP north "Hervanta A B C D" 0.2 E

                //run program
                std::string command = use_vector.at(0);
                for (unsigned int i = 0; i < command.size(); i++)
                {
                    command.at(i) = std::tolower(command.at(i));
                }

                //Quit command
                if (command == "quit")
                {
                   return EXIT_SUCCESS;
                }

                //LINES command
                else if (command == "lines")
                {
                    std::cout << "All tramlines in alphabetical order:" << std::endl;
                    for (auto i = rasse_line_map.begin(); i != rasse_line_map.end(); i++)
                    {
                        std::cout << i->first << std::endl;
                    }
                }

                // LINE command
                else if (command == "line")
                {
                    line_command(rasse_line_map, use_vector);
                }

                //STOPS command
                else if (command == "stops")
                {
                    std::cout << "All stops in alphabetical order:" << std::endl;
                    for (auto i = rasse_stop_map.begin(); i != rasse_stop_map.end(); i++)
                    {
                        std::cout << i->first << std::endl;
                    }

                }

                //STOP commands
                else if (command == "stop")
                {
                    stop_command(rasse_stop_map, use_vector);
                }


                else if (command == "distance")
                {
                    distance(rasse_line_map,use_vector);
                }

                else if (command == "addline")
                {
                    add_line(rasse_line_map,use_vector);
                }

                else if (command == "addstop")
                {
                    add_stop(rasse_line_map, rasse_stop_map, use_vector);
                }


                else if (command == "remove")
                {
                    remove_command(rasse_line_map, rasse_stop_map, use_vector);

                }

                else
                {
                    std::cout<<"Error: Invalid input." << std::endl;
                }
            }
        }

    return EXIT_SUCCESS;

}


