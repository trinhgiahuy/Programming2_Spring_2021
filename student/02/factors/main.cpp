#include <iostream>

using namespace std;

int main()
{
    int n;
    cout << "Enter a positive number: ";
    cin >> n;
    if (n <= 0){
        cout << "Only positive numbers accepted"<<endl;

    }
    else{
        int f1_min = n;
        int f2_min = 1;
        int min = abs(f1_min - f2_min);
        for (int i = 1; i <= n ; i++){
            if (n % i == 0){
                int f1 = n/i;
                int f2 = i;
                int delta = abs(f1-f2);
                if (delta <= min){
                    min = delta;
                    f1_min = f1;
                    f2_min = f2;
                }
            }
        }
        if (f1_min < f2_min){
            cout << n << " = "<<f1_min<<" * "<<f2_min<<endl;
        }else{
            cout << n << " = "<<f2_min<<" * "<<f1_min<<endl;
        }
    }

    return 0;
}
