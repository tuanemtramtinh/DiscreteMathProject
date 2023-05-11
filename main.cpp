#include "expression_process.h"

int main() {
    string infix;
    string logicInfix;
    string logicValue;
    getline(cin, infix);
    getline(cin, logicInfix);
    getline(cin, logicValue);
    cout << "Infix: " << infix << endl;
    cout << "Postfix: " << Infix2Postfix(infix) << endl;
    cout << "Prefix: " << Infix2Prefix(infix) << endl;
    cout << "Postfix result: " << PostfixPrefixCalculator(Infix2Postfix(infix)) << endl;
    cout << "Prefix result: " << PostfixPrefixCalculator(Infix2Prefix(infix)) << endl;
    cout << string(50, '-') << endl;
    cout << "Infix: " << logicInfix << endl;
    cout << "Postfix: " << LogicInfix2Postfix(logicInfix) << endl;
    cout << "Prefix: " << LogicInfix2Prefix(logicInfix) << endl;
    cout << "Postfix result: " << LogicPostfixPrefixCalculator(LogicInfix2Postfix(logicInfix), logicValue) << endl;
    cout << "Prefix result: " << LogicPostfixPrefixCalculator(LogicInfix2Prefix(logicInfix), logicValue) << endl;
    cout << string (22, '-') << "THE END" << string (21, '-');
    return 0;
}
