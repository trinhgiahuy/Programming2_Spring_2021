#include <iostream>

using namespace std;

float InputTemp_f16;
float OutputTemp_16;
int main()
{
    cout << "Enter a temperature: ";
    cin >> InputTemp_f16;
    cout << InputTemp_f16 << " degrees Celsius is " << InputTemp_f16 * 1.8 + 32 << " degrees Fahrenheit" << endl;
    cout << InputTemp_f16 << " degrees Fahrenheit is " << (InputTemp_f16 - 32) / 1.8 << " degrees Celsius" << endl;
    return 0;
}
