#include <iostream>
#include <string>
#include <algorithm>
#include <random>
using namespace std;

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;

    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }else if (word.size()>2){
            //vector<string>::iterator iter;
            //for (auto iter:word)
            shuffle(word.begin()+1,word.end()-1,generator);
            //}

        }
          std::cout << word << std::endl;
    }
}
