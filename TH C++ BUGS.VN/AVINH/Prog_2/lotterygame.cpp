#include<iostream>
#include<cmath>
using namespace std;
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
            for(int i;i<total;i++){
                total=i*total;
                return total;
            }
            for(int j;j<draw;j++){
                total=j*total;
                return total;
            }
            for(int k;k<dif;k++){
                dif=k*dif;
                return dif;
            }
            result=total/(dif*draw);
            return result;
        }
        else{
            std::cout<<"The maximum number of drawn balls is the total amount of balls.";
        }
    }
    else{
        std::cout<<"The number of balls must be a positive number.";
    }
    std::cout<<"The probability of guessing all "<<draw<<"balls correctly is "<<result<<endl;
}