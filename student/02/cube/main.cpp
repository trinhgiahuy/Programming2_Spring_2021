#include<iostream>
#include<cmath>
using namespace std;
int main(){
    int n,area;
    cout<<"Enter a number: ";
    cin>>n;
    area=pow(n,3);
    if(area>2147483647 || area<-2147483647 ){
        cout<<"Error! The cube of "<<n<<" is not "<<area<<endl;
    }
    else{
        cout<<"The cube of "<<n<<" is "<<area<<"."<<endl;
    }
}
