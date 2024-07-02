#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
В стандартном потоке дана одна строка, состоящая из N + 1 целых чисел.
 Первым числом идёт само число N. Далее следуют ещё N чисел, обозначим их за массив A.
 Между собой числа разделены пробелом.

Отсортируйте массив А по модулю и выведите его в стандартный поток.

Ограничения
0 <= N <= 1000

-1000000 <= A[i] <= 1000000
 */

int main() {
    int N;

    cin >> N;

    vector<int> numbers(N);

    for (int i = 0; i < N; ++i) {
        int number;
        cin >> number;
        numbers[i] = number;
    }

    sort(
            begin(numbers),
            end(numbers),
            [](int a, int b){return abs(a) < abs(b);}
    );

    for (int number : numbers) {
        cout << number << " ";
    }

    return 0;
}