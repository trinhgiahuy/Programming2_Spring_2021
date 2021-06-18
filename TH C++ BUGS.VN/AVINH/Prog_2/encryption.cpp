#include<iostream>
#include<string>
#include<cctype>
using namespace std;
int main(){
    string input,encrypt_string;
    string model="abcdefghijklmnopqrstuvwzyx";
    cout<<"Enter the encryption key: ";
    getline(cin,input);
    string model2=model+input;
    if(input.length()!=26){
        cout<<"Error! The encryption key must contain 26 characters.";
    }
    else
    {   for(int i=0;i<=input.length()-1;i++){
            if(islower(input[i]){
                cout<<"Error! The encryption key must contain only lower case characters.";
            }
            else{
                std::size_t leftchar=input.find(input[i]);
                std::size_t rightchar=input.rfind(input[i]);
                //leftchar=input::sizetype find(input[i]);
                //rightchar=input::sizetype rfind(inputp[i]);
                if(leftchar!=rightchar){
                    cout<<"Error! The encryption key must contain all alphabets a-z.";
                }
                else{
                    cout<<"Enter the text to be encrypted: ";
                    //getline(cin,input1);
                    cin>>encrypt_string;
                    for(int j=0;j<26;j++){
                        int new_index;
                        std::size_t index=input.find(encrypt_string[j]);
                        encrypt_string.replace(j,1,model2[26+j]);  
                    }
                }
            }  
           
        }
        cout<<"Encrypted text: "<<encrypt_string;    
    }
    
    

}