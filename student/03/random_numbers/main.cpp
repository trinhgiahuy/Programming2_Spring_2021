#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
    // Implement your function here
std::default_random_engine rand_gen;
    std::cout << "Enter a seed value: ";
    std::string seed_value = "";
    std::cin >> seed_value;
    if (seed_value == "") {
        rand_gen.seed( time(NULL) );
    } else {
        rand_gen.seed( stoi(seed_value) );
    }
    std::cout << endl;
    while (true) {
        std::uniform_int_distribution<int> distribution(lower, upper);
        std::cout << "Your drawn random number is " << distribution(rand_gen) << std::endl;
        std::cout << "Press c to continue or q to quit: " ;
        std::string enter_value = "";

        std::cin >> enter_value;
        if (enter_value == "q") {
            break;
        }else{
            if (enter_value == "c"){
                std::cout<<"\n";
                continue;
            }
        }
        //std::cout << endl;
    }

}

int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound"
             << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
