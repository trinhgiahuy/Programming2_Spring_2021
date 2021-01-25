#include <iostream>


int main()
{
    int n;
    float t1,t2;
    std::cout << "Enter a temperature: ";
    std::cin>>n;
    t1=n*1.8+32;
    t2=(n-32)/1.8;
    std::cout<<n<<" degrees Celsius is "<<t1<<" degrees Fahrenheit "<<std::endl;
    std::cout<<n<<" degrees Fahrenheit is "<<t2<<" degrees Celsius "<<std::endl;

    return 0;
}
