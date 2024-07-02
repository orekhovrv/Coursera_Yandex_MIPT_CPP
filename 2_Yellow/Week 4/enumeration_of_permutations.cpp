// Дано целое положительное число N, не превышающее 9.
// Выведите все перестановки чисел от 1 до N в обратном лексикографическом порядке (см. пример).


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



ostream& operator <<(ostream& stream, vector<int>& array) {
    for (const int value: array) {
        stream << value << ' ';
    }
    stream << endl;
    return stream;
}

int RangeGenerator()
{
    static int i = 1;
    return i++;
}

int main() {

    int n;
    cin >> n;

    vector<int> permutation(n);
    generate(begin(permutation), end(permutation), RangeGenerator);
    reverse(begin(permutation), end(permutation));

    bool is_not_last = true;
    while(is_not_last) {
        cout << permutation;
        is_not_last = prev_permutation(begin(permutation), end(permutation));
    }

    return 0;
}