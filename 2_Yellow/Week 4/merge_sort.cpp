// Напишите шаблонную функцию MergeSort, принимающую два итератора шаблонного типа RandomIt
// и сортирующую заданный ими диапазон с помощью сортировки слиянием.
// Гарантируется, что:
//итераторы типа RandomIt аналогичны по функциональности итераторам вектора и строки,
// то есть их можно сравнивать с помощью операторов <, <=, > и >=, а также вычитать и складывать с числами;
//сортируемые объекты можно сравнивать с помощью оператора <.


#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;


template <typename RandomIt>
tuple<RandomIt, RandomIt, RandomIt, RandomIt> Split(RandomIt range_begin, RandomIt range_end) {
    int half_length = (range_end - range_begin) / 2;
    return {
        range_begin,
        range_begin + half_length,
        range_begin + half_length,
        range_end
    };
}

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }

    vector<typename RandomIt::value_type> elements(range_begin, range_end);

    auto [range_begin_1, range_end_1, range_begin_2, range_end_2] = Split(begin(elements), end(elements)); // Split(range_begin, range_end);

    MergeSort(range_begin_1, range_end_1);
    MergeSort(range_begin_2, range_end_2);

    merge(range_begin_1, range_end_1, range_begin_2, range_end_2, range_begin);
}


int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}