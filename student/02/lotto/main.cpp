#include<iostream>
#include<cmath>

using namespace std;

unsigned long int tinhgiathua(int n){
    if (n==1){
        return 1;
    }
    else
    {
        return n*(tinhgiathua(n-1));
    }

}

long unsigned int probability(int a,int b){
    int A;
    A=tinhgiathua(a)/(tinhgiathua(a-b)*tinhgiathua(b));
    return A;
}

int main(){
    int draw,total,dif;
    cout<<"Enter the total number of lottery balls: ";
    cin>>total;
    cout<<"Enter the number of drawn balls: ";
    cin>>draw;
    dif=total-draw;
    if(total > 0 && draw>0){
        if(dif>0){
            long unsigned int result;
            result=probability(total,draw);
            std::cout<<"The probability of guessing all "<<draw<<" balls correctly is 1/"<<result<<endl;
        }
        else{
            if(dif==0){
                cout<<"The probability of guessing all " << draw<< " balls correctly is 1/1"<<endl;
            }
            else{
                std::cout<<"The maximum number of drawn balls is the total amount of balls." << endl;
            }
        }
    }
    else{
        std::cout<<"The number of balls must be a positive number."<< endl;
    }

}
