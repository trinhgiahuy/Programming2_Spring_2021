#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    cout << setw(7) << "*" << endl;
    for (int i = 1; i < 4; i++)
    {
        cout << setw(7-2*i) << "*" << setw(4*i) << "*" <<  endl;
    }
    for (int i = 2; i >0; i--)
    {
        cout << setw(7-2*i) << "*" << setw(4*i) << "*" <<  endl;
    }
    cout << setw(7) << "*" << endl;
 
    return 0;
}
