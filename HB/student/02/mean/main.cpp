#include <iostream>

using namespace std;

int Count_u16;
int Sum_u16;
int main()
{   
    cout << "From how many integer numbers you want to count the mean value? ";
    cin >> Count_u16;
    if (Count_u16 <= 0)
    {
        cout << "Cannot count mean value from " << Count_u16 << " numbers" << endl;
        
    }
    else
    {
        
        for (int i = 1; i <= Count_u16; i++)
        {
            int Num_u16;
            cout << "Input " << i << ". number: ";
            cin >> Num_u16;
            Sum_u16 += Num_u16;
        }
        cout << "Mean value of the given numbers is " << (float) Sum_u16/Count_u16 << endl;
    
    }
    return 0;
}
