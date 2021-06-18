#include<iostream>
#include<cmath>
using namespace std;
int tinhgiathua(n){
    if (n==1){
        return 1;
    }
    else
    {
        return n*(tinhgiathua(n-1));
    }
    
}

long unsigned int probability(a,b){
    A=tinhgiathua(a)/tinhgiathua(a-b)/tinhgiathua(a-b);
    return int(A);
}
int main(){
    int draw,total,dif;
    long unsigned int result;
    std::cout<<"Enter the total number of lottery balls: ";
    cin>>total;
    std::cout<<"Enter the number of drawn balls: ";
    cin>>draw;
    dif=total-draw;
    if(total > 0 && draw>0){
        if(dif>0){
            return probability(total,draw);
        }
        else{
            std::cout<<"The maximum number of drawn balls is the total amount of balls.";
        }
    }
    else{
        std::cout<<"The number of balls must be a positive number.";
    }
    std::cout<<"The probability of guessing all "<<draw<<"balls correctly is 1/"<<result<<endl;

}