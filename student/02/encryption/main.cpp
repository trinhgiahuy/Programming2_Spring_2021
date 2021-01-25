#include<iostream>
#include<string>
#include<cctype>
/*using namespace std;
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
    {   for(unsigned int i=0;i<input.length()+1;i++){
            if(isupper(input[i])){
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
                    getline(cin,encrypt_string);
                    //cin>>encrypt_string;
                    for(unsigned int j=0;j<encrypt_string.length()+1;j++){
                        //int new_index;
                        std::size_t new_index = model.find(encrypt_string[j]);
                        //std::cout << encrypt_string << " " << encrypt_string[j] << " " << model2[26 + new_index] << "\n";
                        std::cout << model2[26 + new_index];
                        encrypt_string.replace(encrypt_string[j], 1, 1,model2[26+new_index]);
                    }
                }
            }
        }
    cout<<"Encrypted text: "<<encrypt_string<<"\n";
    }



}*/
using namespace std;




int main()
{
    string encrypted = "abcdefghijklmnopqrstuvwxyz";
    string encrypt = "";
    string::size_type len = 0;
    cout << "Enter the encryption key: ";
    cin >> encrypt;
    len = encrypt.length();
    if (len == 26) {
        for (int i = 0; i < 26; i ++) {
            char letter;
            char letter2;
            letter = encrypt.at(i);
            letter2 = encrypted.at(i);
            string::size_type location = 0;
            location = encrypt.find(letter2);
            if ( isdigit(letter) )  {
                cout << "Error! The encryption key must contain only lower case characters.";
                exit(EXIT_FAILURE);
            } else if ( isupper(letter) ){
                cout << "Error! The encryption key must contain only lower case characters.";
                exit(EXIT_FAILURE);
            }
            if ( location == string::npos ) {
                cout << "Error! The encryption key must contain all alphabets a-z.";
                exit(EXIT_FAILURE);
            }
        }
    string text = "";
    cout << "Enter the text to be encrypted: ";
    cin >> text;
    for (unsigned int j = 0; j < text.length(); j++) {
        string::size_type location = 0;
        location = encrypted.find(text.at(j));
        text.at(j) = encrypt.at(location);
    }
    cout << "Encrypted text: " << text << endl;
    } else {
        cout << "Error! The encryption key must contain 26 characters.";
        exit(EXIT_FAILURE);
    }
   }


