#include <iostream>


int main()
{
        int n;
        std::cout<<"How many numbers would you like to have? ";
        std::cin>>n;
        for(int i=1;i<=n;i++)
        {
            if(i%3==0)
            {
                if(i%7==0)
                {
                    std::cout<<"zip boing\n";
                }
                else
                {
                    std::cout<<"zip\n";
                }

            }
            else{
                if(i%7==0){
                    std::cout<<"boing\n";
                }
                 else
                {
                    std::cout<<i<<std::endl;
                }

            }
        }
}

