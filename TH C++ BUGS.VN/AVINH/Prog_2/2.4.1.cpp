#include <iostream>;
using namespace std;
int main()
{
    int n,m1,m2,m3;
    cout<<"How many numbers would you like to have? "<<endl ;
    cin>>n;
    for(int i=1;i<n;i++)
    {
        if(i%3==0)
        {
            if(i%7==0)
            {
                cout<<"zip boing\n";
            }
            else
            {
                cout<<"zip\n";
            }

        }
        else{
            if(i%7==0){
                cout<<"boing\n";
            }
             else
            {
                cout<<i<<endl;
            }
            
        }
        cout<<i<<endl;
    }
}