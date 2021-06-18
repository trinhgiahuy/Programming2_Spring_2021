#include <iostream>
#include <cmath>
using namespace std;

int Num_u16;

int main()
{   
    cout << "Enter a number: ";
    cin >> Num_u16;
    int Pow_u16 = Num_u16*Num_u16*Num_u16;
    if (Num_u16 == 0)
    {
        cout << "The cube of " << Num_u16 << " is " << Pow_u16 << "." <<  endl;
    }
    else if (((Pow_u16%Num_u16) == 0))
    {
        cout << "The cube of " << Num_u16 << " is " << Pow_u16 << "." <<  endl;
        
    }
    else
    {
        cout << "Error! The cube of " << Num_u16 << " is not " << Pow_u16 << "." <<  endl;
    
    }
    return 0;
}
