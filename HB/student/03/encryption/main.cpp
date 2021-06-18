#include <iostream>
#include <string>

using namespace std;

int main() {
     string key = "";
     string original = "abcdefghijklmnopqrstuvwxyz";
     string text = "";
     int flag = 0;
     cout << "Enter the encryption key: ";
     getline(cin, key);

     if (key.length() != 26)
     {
         cout << "Error! The encryption key must contain 26 characters.";
	    return EXIT_FAILURE;
     }
     else
     {
         for (int i = 0; i <= 25; ++i)
         {
             if (key.at(i) < 'a' or key.at(i) > 'z')
             {
                 cout << "Error! The encryption key must contain only lower case characters.";
                 break;
		         return EXIT_FAILURE;
             }
             for (int j = i+1; j <= 25; ++j)
             {
                 if (key.at(i)==key.at(j))
                 {
                     cout << "Error! The encryption key must contain all alphabets a-z.";
                     flag = 1;
                     return EXIT_FAILURE;
                 }
                 if (flag == 1) break;
             }
             if (flag == 1) {
		        break;
		        return EXIT_FAILURE;
	         }
         }
         if (flag == 0)
         {
             cout << "Enter the text to be encrypted: ";
             getline(cin, text);
             string temp = text;
             for (unsigned int i = 0; i <= (text.length()-1); ++i)
             {
                 for (int j = 0; j <= 25; ++j)
                 {
                   if (text.at(i)==original.at(j))
                   {
                      temp.at(i) = key.at(j);   
                   }
                 }
             }
             cout << "Encrypted text: " << temp;
         }
     }
     
}