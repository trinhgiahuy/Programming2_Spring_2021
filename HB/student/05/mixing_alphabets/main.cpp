#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <vector>


int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string line;

    while (std::cin >> line)
    {
        if (line == "END")
        {
            return EXIT_SUCCESS;
        }
        
        std::string word =line;
        if(word.size()>1 )shuffle(++word.begin(), --word.end(), generator);



        std::cout << word << std::endl;
    }
}
