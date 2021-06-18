#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>

using namespace std;
using Data = map<string, int>;

void split(const std::string& s, Data& data, const char delimiter, bool ignore_empty = false) {
	std::vector<std::string> result;
	std::string tmp = s;

	while (tmp.find(delimiter) != std::string::npos)
	{
		std::string new_part = tmp.substr(0, tmp.find(delimiter));
		tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
		if (not (ignore_empty and new_part.empty()))
		{
			try {
				int points = stoi(tmp);
				if (data.find(new_part) != data.end()) {
					data.at(new_part) += points;
				}
				else {
					data.insert({ new_part, points});
				}
			}
			catch (invalid_argument&)
			{
			}
			
		}
	}
	return;
}

bool read_file(Data& data, const string& filename) {
	ifstream file(filename);
	if (not file) {
		return false;
	}
	string line = "";
	while (getline(file, line)) {
		split(line, data, ':', true);
		
	}
	return true;
}




int main() {
	Data data;
	string filename = "";
	cout << "Input file: ";
	getline(cin, filename);
	if (not read_file(data, filename) ){
		cout << "Error! The file " << filename << " cannot be opened." << endl;
		return EXIT_FAILURE;
	}
	else if (!data.empty()) {
		cout << "Final scores:" << endl;
		for (auto x : data) {
			cout << x.first << ": " << x.second << endl;
		}
		return EXIT_SUCCESS;
	}
		
}