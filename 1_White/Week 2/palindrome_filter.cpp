#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Напишите функцию, которая называется PalindromeFilter возвращает vector<string>
 * принимает vector<string> words и int minLength и возвращает все строки из вектора words,
 * которые являются палиндромами и имеют длину не меньше minLength
 * Входной вектор содержит не более 100 строк, длина каждой строки не больше 100 символов.
 * */

bool IsPalindrome(const string& str) {

    int half_end_index = int((str.size() - 1) / 2);
    for (int i = 0; i < half_end_index; ++i) {
        if (str[i] != str[str.size() - 1 - i]) {
            return false;
        }
    }

    return true;
}

vector<string> PalindromeFilter(vector<string> words, const int& minLength) {
    int counter = 0;
    int n = words.size();
    for (int i = 0; i < n; ++i) {
        string word = words[i - counter];
        if (!IsPalindrome(word) || word.size() < minLength) {
            words.erase(words.begin() + i - counter);
            ++counter;
        }
    }
    return words;
}
