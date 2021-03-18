#include <iostream>
#include <string>
#include <stack>
#include <vector>

void operation_(std::stack <double> &num, std::string oper);

std::vector <std::string> split(const std::string& s,
                               const char delimiter,
                               const bool ignore_empty = false) {
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos) {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty())) {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty())) {
        result.push_back(tmp);
    }
    return result;
}


bool is_valid_number(const std::string number) {
    for(unsigned int i = 0; i < number.length(); ++i) {
        if(!('0' <= number[i] && number[i] <= '9')) {
            return false;
        }
    }
    return true;
}


bool is_valid_operator(const std::string oper) {
    if (oper != "+" && oper != "-" && oper != "*" && oper != "/") {
        return false;
    }
    return true;
}

void read_data(std::stack <double> &num, std::stack <std::string> &opera, std::string line) {
    std::vector <std::string> line_split = split(line, ' ');

    if (!is_valid_number(line_split.front())) {
        std::cout << "Error: Expression must start with a number" << std::endl;
        exit(EXIT_FAILURE);
    }
    for (auto part : line_split) {
        if (is_valid_number(part)) {
            num.push(stod(part));
        } else if (is_valid_operator(part)) {
            opera.push(part);
            operation_(num, part);
        } else if (part == "#") {
            continue;
        } else {
            std::cout << "Error: Unknown character" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    if (num.size() != 1) {
        std::cout << "Error: Too few operators" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Correct: " << num.top() << " is the result" << std::endl;
}

void operation_(std::stack <double> &num, std::string oper) {
    double right = num.top();
    num.pop();

    if (num.empty()) {
        std::cout << "Error: Too few operands" << std::endl;
        exit(EXIT_FAILURE);
    }

    double left = num.top();
    num.pop();

    double ans = 0;

    if(oper == "+") {
        ans = left + right;
    } else if (oper == "-") {
        ans = left - right;
    } else if (oper == "*") {
        ans = left * right;
    } else if (oper == "/") {
        if (right == 0) {
            std::cout << "Error: Division by zero" << std::endl;
            exit(EXIT_FAILURE);
        }
        ans = left / right;
    }
    num.push(ans);
}

int main()
{
    std::string line;
    std::cout << "Input an expression in reverse Polish notation (end with #):" << std::endl;
    std::cout << "EXPR> ";
    getline(std::cin,line);

    std::stack <double> num;
    std::stack <std::string> opera;

    read_data(num, opera, line);

    return 0;
}
