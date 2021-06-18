#include <iostream>	
#include <sstream>
#include <stack>
using namespace std;

string extractNextWord(stringstream& string_to_extract) {
	string word = "";
	string_to_extract >> ws;
	
	string_to_extract >> word;
	
	return word;
}

bool reverse_polish(string* tokens, int len, int& result) {
	stack<int> nums;
	//int len = tokens.size();
	for (int i = 0; i < len; i++) {
		string x = *(tokens + i);
		if ((x == "+") || (x == "-") || (x == "*") || (x == "/")) {
			// pop two numbers off the stack                 
			int a = nums.top();
			nums.pop();
			int b = nums.top();
			nums.pop();
			// evaluate and push the result back                 
			switch (x[0]) {
			case '+': nums.push(a + b); break;
			case '-': nums.push(b - a); break;
			case '*': nums.push(b * a); break;
			case '/':
			{
				if (a == 0) {
					cout << "Error: Division by zero" << endl;
					return false;
				}
				nums.push(b / a); break;
			}
			}
		}
		else { // push a number into the stack                 
			int n;
			istringstream(x) >> n;
			nums.push(n);
		}
	}
	if (nums.size()) {
		int xx = nums.top();
		while (nums.size()) {
			nums.pop();
		}
		result = xx;
		return true;
	}
	return false; // error occurs
}

int main()
{
	string input = "";
	cout << "Input an expression in reverse Polish notation (end with #):" << endl;
	cout << "EXPR> ";
	getline(cin, input);
	stringstream ss(input);
	string command[80] = {};
	string* token = command;
	int i = 0;
	int count_number = 0;
	int count_operator = 0;
	int result = 0;
	while (*(token + i) != "#") {
		i++;
		*(token + i) = extractNextWord(ss);
		if ("0" <= *(token + i) && *(token + i) <= "9") count_number++;
		else if (*(token + i) == "+" || *(token + i) == "-" || *(token + i) == "*" || *(token + i) == "/") count_operator++;
		else if (*(token + i) != "#") {
			cout << "Error: Unknown character" << endl;
			return EXIT_FAILURE;
		}
			
		
	}
	if (*(token + 1) == "+" || *(token + 1) == "-" || *(token + 1) == "*" || *(token + 1) == "/") {
		cout << "Error: Expression must start with a number" << endl;
		return EXIT_FAILURE;
	}
	if (count_number > (count_operator + 1)) {
		cout << "Error: Too few operators" << endl;
		return EXIT_FAILURE;
		
	}
	if (count_number < (count_operator + 1)) {
		cout << "Error: Too few operands" << endl;
		return EXIT_FAILURE;
	}
	if (reverse_polish(token, i, result)) {
		cout << "Correct: " << result << " is the result" << endl;
	}
	else {
		return EXIT_FAILURE;
	}
	
}