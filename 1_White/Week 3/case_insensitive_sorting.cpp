#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
//#include <cctype>

using namespace std;

/*
В стандартном потоке дана одна строка, состоящая из числа N и следующих за ним N строк S. Между собой число и строки разделены пробелом.

Отсортируйте строки S в лексикографическом порядке по возрастанию, игнорируя регистр букв, и выведите их в стандартный поток вывода.

Ограничения
0 <= N <= 1000

1 <= |S| <= 15

Каждая строка S[i] может состоять из следующих символов: [0-9,a-z,A-Z]
 */


string GetLowerCase(string input_string) {
    for (char &c : input_string) {
        c = char(tolower(c));
    }
    return input_string;
}

int main() {
    int N;

    cin >> N;

    vector<string> input_array(N);

    for (int i = 0; i < N; ++i) {
        string input_value;
        cin >> input_value;
        input_array[i] = input_value;
    }

    sort(
            begin(input_array),
            end(input_array),
            [](string& a, string& b){return GetLowerCase(a) < GetLowerCase(b);}
    );

    for (string& value : input_array) {
        cout << value << " ";
    }

    return 0;
}