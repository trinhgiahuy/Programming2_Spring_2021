#include <iostream>
#include <fstream>

const int MAXIMUM_INPUT_LENGTH = 80;

int main()
{
    double notation_stack[MAXIMUM_INPUT_LENGTH];
    std::string expr = "";
    std::cout << "Input an expression in "
              << "reverse Polish notation (end with #):\n" << "EXPR> ";

    char c = std::cin.get();

    int i = -1;
    while (c != '#')
    {
        if ((c >= '0') && (c <= '9'))
        {
            double num;
            std::cin.putback(c);
            std::cin >> num;
            notation_stack[++i] = num;
        }
        else if ((c == '+') || (c == '-') || (c == '*') || (c == '/'))
        {
            if (i == -1)
            {
                std::cout << "Error: Expression must start with a number";
                return EXIT_FAILURE;
            }

            if (i >= 1)
            {
                if (c == '+')
                {
                    notation_stack[i - 1] += notation_stack[i];
                        --i;
                }
                else if (c == '-')
                {
                    notation_stack[i - 1] -= notation_stack[i];
                    --i;
                }
                else if (c == '*')
                {
                    notation_stack[i - 1] *= notation_stack[i];
                    --i;
                }
                else if (c == '/')
                {
                    if (notation_stack[i] == 0)
                    {
                        std::cout << "Error: Division by zero";
                        return EXIT_FAILURE;
                    }
                    else
                    {
                        notation_stack[i - 1] /= notation_stack[i];
                        --i;
                    }
                }
            }
            else
            {
                std::cout << "Error: Too few operands";
                return EXIT_FAILURE;
            }
        }
        else
        {
            std::cout << "Error: Unknown character";
            return EXIT_FAILURE;
        }

        do
        {
            c = std::cin.get();
        } while (c == ' ');

    }

    if (i >= 1)
    {
        std::cout << "Error: Too few operators";
        return EXIT_FAILURE;
    }
    else
    {
        std::cout << "Correct: " << *notation_stack << " is the result";
    }

    return EXIT_SUCCESS;
}


