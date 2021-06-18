#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	// Get input file
	string InputFile = "";
	cout << "Input file: ";
	getline(cin, InputFile);

	// Set output file
	string OutputFile = "";
	cout << "Output file: " ;
	getline(cin, OutputFile);

	// Check if input file can be read
	ifstream file_object(InputFile);
	if (not file_object) {
		cout << "Error! The file " << InputFile << " cannot be opened." << endl;
		return EXIT_FAILURE;
	}
	else {
		// create a string vector to contain content
		vector<string> buffer;
		int count = 1;
		string LineFromFile = "";
		// get every line with a number added then store in buffer
		while (getline(file_object, LineFromFile)) {
			LineFromFile = to_string(count) + " " + LineFromFile;
			buffer.push_back(LineFromFile);
			LineFromFile = "";
			count++;
		}
		file_object.close();
		// Write output from buffer
		ofstream file_object(OutputFile);
		for (auto ModifiedLine : buffer)
		{
			file_object << ModifiedLine << endl;
		}
		file_object.close();
	}
}