#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function
std::vector< std::string > split(std::string strings, char separators){
    std::vector< std::string > part_of_strings;
    std::vector< unsigned int > sep_pos;
    std::string temp="";
    strings+=separators;
    int flag=0;
    for(std::string::size_type i=0; i<strings.length();i++){
        if (strings.at(i) == separators){
            
            sep_pos.push_back(i);
        }
    }
    for(std::string::size_type j=0;j<strings.length();j++){
        for(unsigned int i:sep_pos){
            if((i==j)){
                flag=1;
            }
        }
        if(flag==1){
            if(temp.length()!=0){
                part_of_strings.push_back(temp);
                temp="";
            }
            else part_of_strings.push_back(" ");
            flag=0;
        }
        else{
            temp+=strings.at(j);
        }
            
       
    }
    //part_of_strings.pop_back();
    return part_of_strings;
}

std::vector< std::string > split(std::string strings, char separators, bool empty){
    std::vector< std::string > part_of_strings;
    std::vector< unsigned int > sep_pos;
    std::string temp="";
    strings+=separators;
    int flag=0;
    for(std::string::size_type i=0; i<strings.length();i++){
        if (strings.at(i) == separators){
            
            sep_pos.push_back(i);
        }
    }
    for(std::string::size_type j=0;j<strings.length();j++){
        for(unsigned int i:sep_pos){
            if((i==j)){
                flag=1;
            }
        }
        if(flag==1){
            if(temp.length()!=0){
                part_of_strings.push_back(temp);
                temp="";
            }
            if(empty==false) part_of_strings.push_back(" ");
            flag=0;
        }
        else{
            temp+=strings.at(j);
        }
            
       
    }
    //part_of_strings.pop_back();
    return part_of_strings;
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
