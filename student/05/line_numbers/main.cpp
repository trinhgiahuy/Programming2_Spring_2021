#include <iostream>
#include <fstream>  // Notice the required library for file handling
#include <string>

using namespace std;


int main() {
    string filename = "";
    string filename2 = "";
    cout << "Input file: ";
    getline(cin, filename);
    ifstream file_object(filename);
    cout << "Output file: ";
    getline(cin, filename2);

    if ( not file_object ) {
        cout << "Error! The file " << filename << " cannot be opened."<< endl;
        return EXIT_FAILURE;
    } else {

        ofstream file_object2(filename2);
        string line;
        int count = 0;
        while ( getline(file_object, line) ) {
            count ++;
            file_object2 << count << " " << line << endl;
        }
        file_object.close();
        file_object2.close();

    }
}
