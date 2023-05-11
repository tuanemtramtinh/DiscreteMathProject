//
// Created by pc on 5/12/2023.
//

#include "expression_process.h"

unordered_map <char, bool> truth_table;
unordered_map<string, int> pr = {
        {"~", 3},
        {"&", 2},
        {"|", 2},
        {"->",1},
        {"<->", 0},
        {"(", -1},
        {")", -1}
};

/* * * BEGIN IMPLEMENTATION OF EXERCISE 1 * * */

int getPriority(char c){
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

bool digitCheck(char c){
    return c >= '0' && c <= '9';
}

bool operatorCheck(char c){
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')') return true;
    return false;
}

string Infix2Postfix(string infix){
    string postfix;
    stack <char> operator_stack;
    int infix_size = infix.size();
    for (int i = 0; i < infix_size; i++){
        if (digitCheck(infix[i])){
            int j = i;
            while (digitCheck(infix[j])){
                postfix = postfix + infix[j];
                j++;
            }
            i = j - 1;
            postfix += " ";
        }
        if (operatorCheck(infix[i])){
            if (operator_stack.empty() && infix[i] != ')') operator_stack.push(infix[i]);
            else if (infix[i] == ')'){
                while (operator_stack.top() != '('){
                    postfix = postfix + operator_stack.top() + " ";
                    operator_stack.pop();
                }
                operator_stack.pop();
            }
            else if ((infix[i] == '(') || (getPriority(infix[i]) > getPriority(operator_stack.top()))) operator_stack.push(infix[i]);
            else{
                if (!operator_stack.empty()) {
                    while (getPriority(infix[i]) <= getPriority(operator_stack.top())) {
                        postfix = postfix + operator_stack.top() + " ";
                        operator_stack.pop();
                        if (operator_stack.empty()) break;
                    }
                    operator_stack.push(infix[i]);
                }
            }
        }
        if (i == infix_size - 1 && !operator_stack.empty()){
            while (!operator_stack.empty()){
                postfix = postfix + operator_stack.top() + " ";
                operator_stack.pop();
            }
        }
    }
    string temp = "";
    int postfix_size = postfix.size();
    for (int i = 0; i < postfix_size - 1; i++)
        temp += postfix[i];
    postfix = temp;
    return postfix;
}

string Infix2Prefix(string infix){
    stack <string> _stack;
    string temp = Infix2Postfix(infix);
    string prefix;
    int size = temp.size();
    for (int i = 0; i < size; i++){
        if (digitCheck(temp[i])){
            string str;
            int j = i;
            while (temp[j] != ' ' || j > size - 1){
                str = str + temp[j];
                j++;
                if (j == size) break;
            }
            i = j - 1;
            if (i == size - 1) return str;
            else _stack.push(str);
        }
        if (operatorCheck(temp[i])){
            string str = "";
            for (int i = 0; i < 2; i++){
                if (i == 0) str = _stack.top() + str;
                else str = _stack.top() + " " + str;
                _stack.pop();
            }
            string _operator(1, temp[i]);
            str = _operator  + " " + str;
            _stack.push(str);
            prefix = _stack.top();
        }
    }
    return prefix;
}

long double CalculateProcess(long double left, long double right, char c){
    if (c == '+') return left + right;
    if (c == '-') return left - right;
    if (c == '*') return left * right;
    if (c == '/') return left / right;
    return pow(left, right);
}

string ResultProcess(long double s){
    string res = to_string(s);
    if (s == long(s)){
        int pos = res.find('.');
        res = res.substr(0, pos);
    }
    else {
        int i = res.size() - 1;
        while (res[i] == '0') i--;
        res.erase(i + 1, res.size() - 1 - i);
    }
    return res;
}

string PrefixCalculator(string input){
    stack <long double> number;
    int input_size = input.size();
    for (int i = input_size - 1; i >= 0; i--){
        if (digitCheck(input[i])){
            string num = "";
            while (input[i] != ' '){
                num = input[i] + num;
                i--;
            }
            i++;
            number.push(stod(num));
        }
        if (operatorCheck(input[i])){
            long double leftValue = number.top(); number.pop();
            long double rightValue = number.top(); number.pop();
            number.push(CalculateProcess(leftValue, rightValue, input[i]));
        }
    }
    long double s = number.top();
    s = round(s * 10000) / 10000;
    return ResultProcess(s);
}


string PostfixCalculator(string input){
    stack <long double> number;
    int input_size = input.size();
    for (int i = 0; i < input_size; i++){
        if (digitCheck(input[i])){
            string num = "";
            while (input[i] != ' '){
                num += input[i];
                i++;
            }
            i--;
            number.push(stod(num));
        }
        if (operatorCheck(input[i])){
            long double rightValue = number.top(); number.pop();
            long double leftValue = number.top(); number.pop();
            number.push(CalculateProcess(leftValue, rightValue, input[i]));
        }
    }
    long double s = number.top();
    s = round(s * 10000) / 10000;
    return ResultProcess(s);
}

string PostfixPrefixCalculator(string input){
    if (input[0] >= '0' && input[0] <= '9') return PostfixCalculator(input);
    return PrefixCalculator(input);
}

/* * * END IMPLEMENTATION OF EXERCISE 1 * * */

/* * * BEGIN IMPLEMENTATION OF EXERCISE 2 * * */

int min(int a, int b){
    if (a > b) return b;
    return a;
}

bool alphabetCheck(char c){
    return c >= 'a' && c <= 'z';
}

string ImplicationEquivalentConvert(string infix, int& i){
    int j = i;
    string temp = "";
    while (!alphabetCheck(infix[j]) && infix[j] != '(' && infix[j] != ')' && infix[i] != ' ') {
        temp = temp + infix[j];
        j++;
        if (infix[j] == '&' || infix[j] == '|' || infix[j] == '~' || infix[i] == ' ') break;
    }
    if (j != i) i = j - 1;
    return temp;
}

string LogicInfix2Postfix(string infix){
    stack <string> _stack;
    string postfix = "";
    int infix_size = infix.size();
    for (int i = 0; i < infix_size; i++){
        if (alphabetCheck(infix[i])) postfix = postfix + infix[i];
        else{
            string temp = "";
            if (infix[i] != '(' && infix[i] != ')' && infix[i] != ' ') {
                temp = ImplicationEquivalentConvert(infix, i);
            }
            else if (infix[i] != ' ') temp = temp + infix[i];
            if (_stack.empty() && temp != ")") _stack.push(temp);
            else if (temp == ")"){
                while (_stack.top() != "("){
                    postfix = postfix + _stack.top();
                    _stack.pop();
                }
                _stack.pop();
            }
            else if (temp == "(" || pr[temp] > pr[_stack.top()]) _stack.push(temp);
            else {
                if (!_stack.empty()){
                    while (pr[temp] <=pr[_stack.top()]){
                        postfix = postfix + _stack.top();
                        _stack.pop();
                        if (_stack.empty()) break;
                    }
                    _stack.push(temp);
                }
            }
        }
        if (i == infix_size - 1 && !_stack.empty()){
            while (!_stack.empty()){
                postfix = postfix + _stack.top();
                _stack.pop();
            }
        }
    }
    return postfix;
}

string LogicInfix2Prefix(string infix){
    stack <string> _stack;
    string temp = LogicInfix2Postfix(infix);
    string prefix = "";
    int size = temp.size();
    for (int i = 0; i < size; i++){
        if (alphabetCheck(temp[i])){
            string alpha = "";
            if (temp[i + 1] == '~'){
                alpha = alpha + temp[i + 1] + temp[i];
                i++;
            }
            else alpha += temp[i];
            if (i == size - 1) return alpha;
            _stack.push(alpha);
        }
        else{
            string _operator("");
            string res("");
            if (temp[i] == '<' || temp[i] == '-' || temp[i] == '>') {
                int j = i;
                while (temp[j] == '<' || temp[j] == '-' || temp[j] == '>') {
                    _operator = _operator + temp[j];
                    j++;
                    if (_operator == "<->" || _operator == "->") break;
                }
                i = j - 1;
            }
            else _operator += temp[i];
            int stack_size = _stack.size();
            for (int i = 0; i < min(2, stack_size); i++){
                res = _stack.top() + res;
                _stack.pop();
            }
            res = _operator + res;
            _stack.push(res);
            prefix = _stack.top();
        }
    }
    return prefix;
}

void CreateTruthTable(string value){
    int value_size = value.size();
    for (int i  = 0; i < value_size / 2; i++){
        if (alphabetCheck(value[i])){
            int pos = value_size - (value_size / 2);
            truth_table.emplace(value[i], value[i + pos] - '0');
            i++;
        }
        else break;
    }
}

string OperatorMakePostfix(string input, int &index){
    string _operator = "";
    if (input[index] == '<' || input[index] == '-' || input[index] == '>'){
        while (input[index] == '<' || input[index] == '-' || input[index] == '>'){
            _operator += input[index];
            index++;
            if (_operator == "<->" || _operator == "->") break;
        }
        index--;
    } else _operator += input[index];
    return _operator;
}

string OperatorMakePrefix(string input, int &index){
    string _operator = "";
    if (input[index] == '<' || input[index] == '-' || input[index] == '>'){
        while (input[index] == '<' || input[index] == '-' || input[index] == '>'){
            _operator = input[index] + _operator;
            index--;
            if (input[index] != '<' && _operator == "->") break;
            if (_operator == "<->") break;
        }
        index++;
    } else _operator += input[index];
    return _operator;
}

bool CalculateProcess(bool left, bool right, string x){
    if (x == "&") return left & right;
    if (x == "|") return left || right;
    if (x == "~") return !left;
    if (x == "->") return !left || right;
    return (left && right) || (!left && !right);
}

string PostfixCalculator(string input, string value){
    stack <bool> truthValue;
    CreateTruthTable(value);
    int input_size = input.size();
    for (int i = 0; i < input_size; i++){
        if (alphabetCheck(input[i])) truthValue.push(truth_table[input[i]]);
        else{
            string _operator = OperatorMakePostfix(input, i);
            bool rightValue = truthValue.top(); truthValue.pop();
            if (!truthValue.empty()) {
                if (_operator != "~"){
                    bool leftValue = truthValue.top(); truthValue.pop();
                    truthValue.push(CalculateProcess(leftValue, rightValue, _operator));
                }
                else truthValue.push(CalculateProcess(rightValue, 1, _operator));
            }
            else truthValue.push(CalculateProcess(rightValue, 1, _operator));
        }
    }
    bool res = truthValue.top();
    truthValue.empty();
    truth_table.clear();
    if (res) return "TRUE";
    return "FALSE";
}

string PrefixCalculator(string input, string value){
    stack <bool> truthValue;
    CreateTruthTable(value);
    int input_size = input.size();
    for (int i = input_size - 1; i >= 0; i--){
        if (alphabetCheck(input[i])) truthValue.push(truth_table[input[i]]);
        else{
            string _operator = OperatorMakePrefix(input, i);
            bool leftValue = truthValue.top(); truthValue.pop();
            if (!truthValue.empty()){
                if (_operator != "~"){
                    bool rightValue = truthValue.top(); truthValue.pop();
                    truthValue.push(CalculateProcess(leftValue, rightValue, _operator));
                }
                else truthValue.push(CalculateProcess(leftValue, 1, _operator));
            }
            else truthValue.push(CalculateProcess(leftValue, 1, _operator));
        }
    }
    bool res = truthValue.top();
    truthValue.empty();
    truth_table.clear();
    if (res) return "TRUE";
    return "FALSE";
}

string LogicPostfixPrefixCalculator(string input,string value){
    if (alphabetCheck(input[0])) return PostfixCalculator(input, value);
    return PrefixCalculator(input, value);
}

/* * * END IMPLEMENTATION OF EXERCISE 2 * * */