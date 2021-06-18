#include <iostream>

using namespace std;

int Num_u16;

int main()
{   
    int ZipActive_flag = 1;
    int BoingActive_flag = 1;
    cout << "How many numbers would you like to have? ";
    cin >> Num_u16;
    for (int i = 1; i <= Num_u16; i++ )
    {
        if ((((i % 3) == 0) || ((i % 7) == 0)) \
            && (ZipActive_flag == 1) )
        {
            cout << (((i % 3) == 0)?("zip"):"") \
                 << ((((i % 7) == 0)  && ((i % 3) == 0) && (BoingActive_flag == 1))?(" "):"") \
                 << ((((i % 7) == 0) && (BoingActive_flag == 1))?("boing"):"") \
                 << endl;
        }
        else 
        {
            cout << i << endl;
        }
    }
    return 0;
}
