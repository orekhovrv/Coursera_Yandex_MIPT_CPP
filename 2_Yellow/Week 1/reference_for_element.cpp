#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;


//Реализуйте шаблонную функцию GetRefStrict, которая на вход принимает:
// map и значение ключа k.
// Если элемент по ключу k в коллекции отсутствует, то функция должна бросить исключение runtime_error, иначе вернуть ссылку на элемент в коллекции.
//
//Пример использования функции

template <typename T, typename V>
V& GetRefStrict(map<T, V>& collection, T k) {
    if (collection.find(k) == end(collection)) {
        throw runtime_error("error");
    } else {
        return collection[k];
    }
}




int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue
}