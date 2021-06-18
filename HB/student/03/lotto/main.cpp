/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

using namespace std;

unsigned long int Factorial_n(int n);
unsigned long int Sample_space(int total, int chosen);

unsigned long int Factorial_n(int n)
{
    unsigned long int factorial=1;
    for(int i = 1; i <=n; i++)
    {
        factorial *= i;
    }
    return factorial;
}

unsigned long int Sample_space(int total, int chosen)
{
    return (Factorial_n(total)/Factorial_n(total-chosen)/Factorial_n(chosen));
}


int main()
{
    int total_ball;
    int chosen_ball;
    cout << "Enter the total number of lottery balls: ";
    cin >> total_ball;
    cout << "Enter the number of drawn balls: ";
    cin >> chosen_ball;
    
    if ((total_ball < 0) || (chosen_ball < 0))
    {
        cout << "The number of balls must be a positive number." << endl;
    }
    else if (total_ball < chosen_ball) 
    {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
    }
    else 
    {
        cout << "The probability of guessing all " << chosen_ball << " balls correctly is 1/" << Sample_space(total_ball,chosen_ball) << endl;
    }
   
    return 0;
}

