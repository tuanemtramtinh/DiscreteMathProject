//
// Created by pc on 5/12/2023.
//

#ifndef EXPRESSION_PROCESS_H
#define EXPRESSION_PROCESS_H

#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <cmath>

using namespace std;

/* * * BEGIN IMPLEMENTATION OF EXERCISE 1 * * */

int getPriority(char c);
bool digitCheck(char c);
bool operatorCheck(char c);
string Infix2Postfix(string infix);
string Infix2Prefix(string infx);
long double CalculateProcess(long double left, long double right, char c);
string ResultProcess(long double s);
string PrefixCalculator(string input);
string PostfixCalculator(string input);
string PostfixPrefixCalculator(string input);

/* * * END IMPLEMENTATION OF EXERCISE 1 * * */




int min(int a, int b);
bool alphabetCheck(char c);
bool logicOperatorCheck(string c);
string ImplicationEquivalentConvert(string infix, int &i);
string LogicInfix2Postfix(string infix);
string LogicInfix2Prefix(string infix);
void CreateTruthTable(string value);
string OperatorMakePostfix(string input, int &index);
string OperatorMakePrefix(string input, int &index);
bool CalculateProcess(bool left, bool right, string x);
string PostfixCalculator(string input, string value);
string PrefixCalculator(string input, string value);
string LogicPostfixPrefixCalculator(string input,string value);


#endif //EXPRESSION_PROCESS_H
