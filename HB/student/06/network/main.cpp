#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;
using Network = map<string, vector<string>>;


const string HELP_TEXT = "S = store id1 i2\n P = print id\n"
"C = count id\n D = depth id";



vector<string> split(const string& s, const char delimiter, bool ignore_empty = false) {
	std::vector<string> result;
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

void add_relationship(Network& net, string& boss, string& employee) {

	net.insert({ boss,{} });
	net.insert({ employee,{} });
	net.at(boss).push_back(employee);
}

void print(const Network& net, const string& name, int level = 0) {
	cout << string(2 * level, '.') << name << endl;
	if (net.at(name).empty()) {
		return;
	}
	else {
		for (auto employee : net.at(name)) {
			print(net, employee, level + 1);
		}
	}

}

int count(const Network& net, const string& name) {
	int sum = net.at(name).size();
	if (net.at(name).empty()) {
		return 0;
	}
	else {
		for (auto employee : net.at(name)) {
			sum += count(net, employee);
		}
		return sum;
	}
}

int find_depth(const Network& net, const string& name, int level = 0) {
	if (net.at(name).empty()) {
		int one_path = level;
		level = 0;
		return one_path + 1 ;
	}
	else {
		int max = 0;
		for (auto employee : net.at(name)) {
			int depth = find_depth(net, employee, level+1);
			if (depth > max)
				max = depth;
		}
		return max;
	}
}

int main()
{
	// TODO: Implement the datastructure here

	Network net;
	while (true) {
		string line;
		cout << "> ";
		getline(std::cin, line);
		vector<string> parts = split(line, ' ', true);

		string command = parts.at(0);

		if (command == "S" or command == "s") {
			if (parts.size() != 3) {
				cout << "Erroneous parameters!" << endl << HELP_TEXT;
			}
			string id1 = parts.at(1);
			string id2 = parts.at(2);
			add_relationship(net, id1, id2);


		}
		else if (command == "P" or command == "p") {
			if (parts.size() != 2) {
				cout << "Erroneous parameters!" << endl << HELP_TEXT;
			}
			string id = parts.at(1);
			print(net, id);
			// TODO: Implement the command here!

		}
		else if (command == "C" or command == "c") {
			if (parts.size() != 2) {
				cout << "Erroneous parameters!" << endl << HELP_TEXT;
			}
			string id = parts.at(1);
			cout << count(net, id) << endl;
			// TODO: Implement the command here!

		}
		else if (command == "D" or command == "d") {
			if (parts.size() != 2) {
				cout << "Erroneous parameters!" << endl << HELP_TEXT;
			}
			string id = parts.at(1);
			cout << find_depth(net, id) << endl;
			// TODO: Implement the command here!

		}
		else if (command == "Q" or command == "q") {
			return EXIT_SUCCESS;
		}
		else {
			cout << "Erroneous command!" << endl << HELP_TEXT;
		}
	}
}
