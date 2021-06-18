#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>

using namespace std;
using Data = map<string, vector<int>>;

std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false) {
	std::vector<std::string> result;
	std::string tmp = s;

	while (tmp.find(delimiter) != std::string::npos)
	{
		std::string new_part = tmp.substr(0, tmp.find(delimiter));
		tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
		if (not (ignore_empty and new_part.empty()))
		{
			result.push_back(new_part);
		}
	}
	if (not (ignore_empty and tmp.empty()))
	{
		result.push_back(tmp);
	}
	return result;
}


bool read_file(Data& data, const string& filename) {
	ifstream file(filename);
	if (not file) {
		return false;
	}
	string line;
	int line_number = 0;
	while (getline(file, line)) {
		++line_number;
		vector<string> words = split(line, ' ', true);
	
		for (string word : words) {
			if (data.find(word) == data.end()) {
				data.insert({ word,  {line_number} });
			}
			else if (data.at(word).back() != line_number) {
				data.at(word).push_back(line_number);
			}
			
		}
	}
	return true;

}


void print(const Data& data) {
	for (auto element : data) {
		cout << element.first << " "
			<< element.second.size() << ": ";
		for (auto line : element.second) {
			cout << line;
			if (line != *--element.second.end()) {
				cout << ", ";
			}
		}
		cout << endl;
	}
}


int main() {
	Data data;
	string filename = "test.txt";
	cout << "Input file: ";
	getline(cin, filename);
	if (not read_file(data, filename) ){
		cout << "Error! The file " << filename << " cannot be opened." << endl;
		return EXIT_FAILURE;
	}
	else if (!data.empty()) {
		print(data);
		return EXIT_SUCCESS;
	}
		
}