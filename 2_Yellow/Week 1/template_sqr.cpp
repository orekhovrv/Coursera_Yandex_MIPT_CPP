#include <iostream>
#include <vector>
#include <map>
//#include <pair>

using namespace std;


//Реализуйте шаблонную функцию Sqr, которая работает не только для чисел, но и для контейнеров.
// Функция должна возвращать копию исходного контейнера, модифицировав его следующим образом:
//для vector элементы нужно возвести в квадрат;
//для map в квадрат нужно возвести только значения, но не ключи;
//для pair в квадрат нужно возвести каждый элемент пары.

//Функция должна корректно работать не только для контейнеров, состоящих из чисел, но и для составных объектов, например, векторов словарей пар чисел.
// Для успешной сдачи решения необходимо сделать предварительное объявление шаблонных функций перед всеми шаблонными функциями.

template <typename T> T Sqr(T value);

template <typename T> vector<T> Sqr(vector<T> container);

template <typename T, typename V> map<T, V> Sqr(map<T, V> container);

template <typename T, typename V> pair<T, V> Sqr(pair<T, V> container);


template <typename T>
T Sqr(T value) {
    return value * value;
}

template <typename T>
vector<T> Sqr(vector<T> container) {
    for (T& value: container) {
        value = Sqr(value);
    }
    return container;
}

template <typename T, typename V>
map<T, V> Sqr(map<T, V> container) {
    for (auto& [key, value]: container) {
        value = Sqr(value);
    }
    return container;
}

template <typename T, typename V>
pair<T, V> Sqr(pair<T, V> container) {
    return  pair(Sqr(container.first),  Sqr(container.second));
}



int main() {
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
            {4, {2, 2}},
            {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
}