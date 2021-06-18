// Rasse Project!
// In this project, I implemented a database using map structure 
// with key as string, and key's data as a vector of string
// - Input data get from a file using fstream library
// - To manipulate command, use stringstream library
// - Algorithm library is added to use sort function.
//
// Student's name: Anh Huy Bui
// Student's number: 293257

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;
using Stations = vector<string>;
using Tramways = map<string, Stations>;

void print_rasse() {
	cout << \
		"=====//==================//=== \n\
  __<<__________________<<__	\n\
 | ____ ____ ____ ____ ____ |   \n\
 | |  | |  | |  | |  | |  | |	\n\
 |_|__|_|__|_|__|_|__|_|__|_|	\n\
.|                  RASSE   |.	\n\
:|__________________________|:	\n\
___(o)(o)___(o)(o)___(o)(o)____ \n\
-------------------------------" << endl;
}

// Define compare function for alphabetical sort
bool compareFunction(string first_word, string second_word) {
	return first_word < second_word;
}

// Extracting data from a string (which is a command line in this case)
string extractNextWord(stringstream& string_to_extract) {
	string word = "";
	string_to_extract >> ws;
	// Check if there are 2 words have boundaries are double quote
	if (string_to_extract.peek() == '"') {
		// Inorge the first quote
		string_to_extract.ignore();
		// Get word until the second quote is read
		getline(string_to_extract, word, '"');
	}
	else {
		string_to_extract >> word;
	}
	return word;
}

// Get command case to uppercase
void stringToUpper(string& s) {
	for (unsigned int i = 0; i < s.length(); i++) {
		s[i] = toupper(s[i]);
	}
}

// Split string with a delimiter and return in elements of a vector
vector<string> split(const string& s, const char delimiter, bool ignore_empty = false) {
	vector<string> result = {};
	string tmp = s;
	while (tmp.find(delimiter) != string::npos)
	{
		string new_part = tmp.substr(0, tmp.find(delimiter));
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

// Read file from drive
bool readFile(Tramways& tramways, const string& file) {
	ifstream file_object(file);
	if (not file_object) {
		cout << "Error: File could not be read." << endl;
		return false;
	}
	string line_read_from_file = "";
	// get every line in file
	while (getline(file_object, line_read_from_file)) {
		// Split line content with ";" and store in a vector
		vector<string> line_and_station = split(line_read_from_file, ';');
		// Check if file correspond to the specification, with 2 elements (line;station)
		if (line_and_station.size() == 2) {
			string line_in_file = line_and_station.at(0);
			string station_in_file = line_and_station.at(1);
			// Insert line as a new key with no data to map 
			tramways.insert({ line_in_file,{} });
			for (string elements : tramways.at(line_in_file)) {
				// Check if the input file does include duplicates
				if (elements == station_in_file) {
					cout << "Error: Station/line already exists." << endl;
					return false;
				}
			}
			// Insert data to key
			tramways.at(line_in_file).push_back(station_in_file);
		}
		else {
			cout << "Error: Invalid format in file." << endl;
			return false;
		}
	}
	file_object.close();
	return true;
}

// Print all keys (lines) in tramways map
void printLines(const Tramways& tramways) {
	// Set an iterator to scan all keys 
	Tramways::const_iterator iter = tramways.begin();
	cout << "All tramlines in alphabetical order:" << endl;
	while (iter != tramways.end()) {
		// print key
		cout << iter->first << endl;
		iter++;
	}
}

// Print all stations in one line (elements in vector with a given key) 
void printStationsInLine(stringstream& command_data, const Tramways& tramways) {
	// Get "line" (key) from command line
	string line_input = extractNextWord(command_data);
	if (line_input.empty()) {
		cout << "Error: Invalid input." << endl;
		return;
	}
	if (tramways.find(line_input) == tramways.end()) {
		cout << "Error: Line could not be found." << endl;
		return;
	}
	cout << "Line " << line_input
		<< " goes through these stations in the order they are listed:" << endl;
	// For loop to print all elements of vector with input key
	for (string stations_in_line : tramways.at(line_input)) {
		cout << " - " << stations_in_line << endl;
	}
}

// Print all elements of all vectors in map
void printAllStations(const Tramways& tramways) {
	// Create a vector that contains all stations for later print
	vector<string> station_container = {};
	Tramways::const_iterator iter = tramways.begin();
	// While loop to get all keys, which are lines
	while (iter != tramways.end()) {
		// "iter -> second" is a vector contains all stations in a line 
		for (string stations_in_line : iter->second) {
			// Check if station is not already in "station_container" vector
			if (find(station_container.begin(), station_container.end(), stations_in_line) == station_container.end()) {
				station_container.push_back(stations_in_line);
			}
		}
		iter++;
	}
	// sort all element in station_container in alphabetical order
	sort(station_container.begin(), station_container.end(), compareFunction);
	cout << "All stations in alphabetical order:" << endl;
	// Print all sorted element 
	for (string stations_in_order : station_container) {
		cout << stations_in_order << endl;
	}
}

// Print all keys contain given vector element
void printLinesContainStation(stringstream& command_data, const Tramways& tramways) {
	string station_input = extractNextWord(command_data);
	if (station_input.empty()) {
		cout << "Error: Invalid input." << endl;
		return;
	}
	// Create "line_container" vector to contain output
	vector<string> line_container = {};
	Tramways::const_iterator iter = tramways.begin();
	// iterator to scan through every key in map
	while (iter != tramways.end()) {
		for (string station_in_line : iter->second) {
			// Check if the given station can be found in this line 
			if (station_input == station_in_line and
				// and this line is not in the container
				find(line_container.begin(), line_container.end(), (iter->first)) == line_container.end()) {
				line_container.push_back(iter->first);
				break;
			}
		}
		iter++;
	}
	// If there is no output, return
	if (line_container.size() == 0) {
		cout << "Error: Station could not be found." << endl;
		return;
	}
	cout << "Station " << station_input
		<< " can be found on the following lines:" << endl;
	// Sort all lines contained in "line_container"
	sort(line_container.begin(), line_container.end(), compareFunction);
	// Print all sorted elements of "line_container"
	for (string line_in_order : line_container) {
		cout << " - " << line_in_order << endl;
	}
}

// Add new key to map
void addNewLine(stringstream& command_data, Tramways& tramways) {
	string new_line_input = extractNextWord(command_data);
	if (new_line_input.empty()) {
		cout << "Error: Invalid input." << endl;
		return;
	}
	if (tramways.find(new_line_input) != tramways.end()) {
		cout << "Error: Station/line already exists." << endl;
		return;
	}
	// add key with empty data
	tramways.insert({ new_line_input,{} });
	cout << "Line was added." << endl;
}

// Add new element to a vector of given key
void addNewStation(stringstream& command_data, Tramways& tramways) {
	string line_input = extractNextWord(command_data);
	string new_station = extractNextWord(command_data);
	string next_station = extractNextWord(command_data);
	if (line_input.empty() or new_station.empty()) {
		cout << "Error: Invalid input." << endl;
		return;
	}
	// Check the given key is exist
	if (tramways.find(line_input) == tramways.end()) {
		cout << "Error: Line could not be found." << endl;
		return;
	}
	vector<string>& stations_in_line = tramways.at(line_input);
	// Check if new element is already in vector of given key
	if (find(stations_in_line.begin(), stations_in_line.end(), new_station) != stations_in_line.end()) {
		cout << "Error: Station/line already exists." << endl;
		return;
	}
	// Check if no next station input
	if (next_station.empty()) {
		// add new station in the last of vector 
		stations_in_line.push_back(new_station);

	}
	else {
		// If not, find the position of next station
		Stations::iterator iter = find(stations_in_line.begin(), stations_in_line.end(), next_station);
		// Add new station in that position
		stations_in_line.insert(iter, new_station);
	}
	cout << "Station was added." << endl;
}

// Remove given station in all keys
void removeStation(stringstream& command_data, Tramways& tramways) {
	string station_input = extractNextWord(command_data);
	// bool variable to check if given station is found anywhere in whole map
	bool station_found = false;
	if (station_input.empty()) {
		cout << "Error: Invalid input." << endl;
		return;
	}
	Tramways::iterator iter = tramways.begin();
	// iterator to scan through every key in map
	while (iter != tramways.end()) {
		vector<string>& station_container = tramways.at(iter->first);
		// Find position of given station in vector of this key
		Stations::iterator station_position = find(station_container.begin(), station_container.end(), station_input);
		// If station exists 
		if (station_position != station_container.end()) {
			// remove that station from vector and found_flag is true
			station_container.erase(station_position);
			station_found = true;
		}
		iter++;
	}
	// If given station is not exist in database
	if (!station_found) {
		cout << "Error: Station could not be found." << endl;
		return;
	}
	cout << "Station was removed from all lines." << endl;
}

int main()
{
	print_rasse();
	Tramways tramways;
	string filename = "";
	cout << "Give a name for input file: ";
	getline(cin, filename);
	if (!readFile(tramways, filename)) {
		return EXIT_FAILURE;
	}
	while (true) {
		string command_input;
		cout << "tramway> ";
		getline(cin, command_input);
		stringstream command_for_extracting(command_input);
		// Extract first word of command line
		string cmd = extractNextWord(command_for_extracting);
		stringToUpper(cmd);
		if (cmd.empty()) {
			continue;
		}
		else if (cmd == "QUIT") {
			break;
		}
		else if (cmd == "LINES") {
			printLines(tramways);
		}
		else if (cmd == "LINE") {
			printStationsInLine(command_for_extracting, tramways);
		}
		else if (cmd == "STATIONS") {
			printAllStations(tramways);
		}
		else if (cmd == "STATION") {
			printLinesContainStation(command_for_extracting, tramways);
		}
		else if (cmd == "ADDLINE") {
			addNewLine(command_for_extracting, tramways);
		}
		else if (cmd == "ADDSTATION") {
			addNewStation(command_for_extracting, tramways);
		}
		else if (cmd == "REMOVE") {
			removeStation(command_for_extracting, tramways);
		}
		else {
			cout << "Error: Invalid input." << endl;
		}




	}
	return EXIT_SUCCESS;
}