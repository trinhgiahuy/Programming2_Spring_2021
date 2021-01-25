#include <iostream>
using namespace std;

// Write here a function counting the mean value

int main()
{
    int n,value;
    std::cout << "From how many integer numbers you want to count the mean value? ";
    std::cin>>n;
    if(n<=0){
        std::cout<< "Cannot count mean value from "<<n<<" numbers\n";
    }
    else{
        float mean =0;
        for(int i=1;i<=n;i++){
        std::cout<<"Input "<<i<<". number: ";
        std::cin>>value;
        mean+=value;
        }
    //cout.setf(ios::fixed);
    //cout.setf(ios::showpoint);
    //cout.precision(1);
    std::cout<<"Mean value of the given numbers is "<<mean/n<<std::endl;
    }
}
