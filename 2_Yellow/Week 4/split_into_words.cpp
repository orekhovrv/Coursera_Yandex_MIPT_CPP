#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

// Напишите функцию SplitIntoWords, разбивающую строку на слова по пробелам.
// Гарантируется, что:
//строка непуста;
//строка состоит лишь из латинских букв и пробелов;
//первый и последний символы строки не являются пробелами;
//строка не содержит двух пробелов подряд.
//
//Подсказка
//Рекомендуется следующий способ решения задачи:
//искать очередной пробел с помощью алгоритма find;
//создавать очередное слово с помощью конструктора строки по двум итераторам.



vector<string> SplitIntoWords(const string& s) {
    vector<string> result;
    auto begin_iterator = begin(s);

    while(begin_iterator != end(s)) {
        auto separator_iterator = find(begin_iterator, end(s), ' ');
        result.push_back(string(begin_iterator, separator_iterator));
        begin_iterator =  separator_iterator != end(s) ? separator_iterator + 1: separator_iterator;

    }

    return result;
}


int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}