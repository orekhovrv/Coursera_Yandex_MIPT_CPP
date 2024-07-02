// Напишите шаблонную функцию FindGreaterElements,
// принимающую множество elements объектов типа T и ещё один объект border типа T
// и возвращающую вектор из всех элементов множества, бо́льших border, в возрастающем порядке.

#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;


template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
    // variant 1
//    auto iterator = begin(elements);
//    while(iterator != end(elements) && *iterator <= border) {
//        iterator++;
//    }

    // variant 2
    auto iterator = find_if(
        begin(elements),
        end(elements),
        [border](const T& value) {return value > border;}
    );

    return vector(iterator, end(elements));
}



//int main() {
//    for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
//        cout << x << " ";
//    }
//    cout << endl;
//
//    string to_find = "Python";
//    cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
//    return 0;
//}
