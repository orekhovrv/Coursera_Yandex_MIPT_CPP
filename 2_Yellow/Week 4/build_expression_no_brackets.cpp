#include <iostream>
#include <string>

using namespace std;

//Модифицируйте решение предыдущей части так, чтобы предыдущее выражение обрамлялось скобками лишь при необходимости,
// то есть только в том случае, когда очередная операция имеет бо́льший приоритет, чем предыдущая.


bool IsBracketsNeeded(const char last_operation,const char current_operation) {
    return (last_operation == '+' || last_operation == '-') && (current_operation == '*' || current_operation == '/');
}


int main() {
    int n;
    string result;

    cin >> result >> n;

    char operation, last_operation;
    string operand;
    for (int i = 0; i < n; ++i, last_operation = operation) {
        cin >> operation >> operand;
        if (IsBracketsNeeded(last_operation, operation)) {
            result.insert (0, 1, '(');
            result.append(") ");
        }
        result.append(" ").append(string(1, operation).append(" ").append(operand));
    }

    cout << result;

    return 0;
}