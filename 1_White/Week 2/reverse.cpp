#include <vector>
#include <iostream>

using namespace std;


/* Реализуйте функцию void Reverse(vector<int>& v), которая переставляет элементы вектора в обратном порядке.
 * Гарантируется, что вектор v имеет ненулевую длину. */

void Swap(int& a, int& b) {
    a += b;
    b = a - b;
    a -= b;
}

void Reverse(vector<int>& v) {
    int half_end_index = int((v.size() - 1) / 2);
    for (int i = 0; i < half_end_index; ++i) {
        Swap(v[i], v[v.size() - 1 - i]);
    }
}

//int main() {
//    vector<int> v = {1, 2, 3, 4, 5};
//
//    Reverse(v);
//
//    for(int i: v) {
//        cout << i << " ";
//    }
//
//    return 0;
//}
