#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

// Если диапазон содержит меньше 2 элементов, выйти из функции.
//Создать вектор, содержащий все элементы текущего диапазона.
//Разбить вектор на три равные части. (В этой задаче гарантируется, что длина передаваемого диапазона является степенью тройки, так что вектор всегда можно разбить на три равные части.)
//Вызвать функцию MergeSort от каждой части вектора.
//Слить первые две трети вектора с помощью алгоритма merge, сохранив результат во временный вектор с помощью back_inserter.
//Слить временный вектор из предыдущего пункта с последней третью вектора из п. 2, записав полученный отсортированный диапазон вместо исходного.

// Напишите реализацию функции, не копируя сортируемые элементы
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }

//    const int range_length = range_end - range_begin;
    RandomIt delimiter_1 = range_begin + (range_end - range_begin) / 3;
    RandomIt delimiter_2 = range_begin + 2 * (range_end - range_begin) / 3;

    MergeSort(range_begin, delimiter_1);
    MergeSort(delimiter_1, delimiter_2);
    MergeSort(delimiter_2, range_end);

    vector<typename RandomIt::value_type> temporary_vector;
    merge(
            make_move_iterator(range_begin),
            make_move_iterator(delimiter_1),
            make_move_iterator(delimiter_1),
            make_move_iterator(delimiter_2),
            back_inserter(temporary_vector)
    );
    vector<typename RandomIt::value_type> temporary_vector_2;
    auto a = make_move_iterator(temporary_vector.begin());
    auto b = make_move_iterator(delimiter_2);
    auto c = make_move_iterator(temporary_vector.end());
    auto d = make_move_iterator(range_end);
    merge(
            make_move_iterator(temporary_vector.begin()),
            make_move_iterator(temporary_vector.end()),
            make_move_iterator(delimiter_2),
            make_move_iterator(range_end),
            range_begin
    );
}


void TestIntVector() {
//  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  vector<int> numbers = {1,2,3, 4,5,6, 7,8,9};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
