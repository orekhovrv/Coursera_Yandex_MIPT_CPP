#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;


/* Напишите функцию, которая называется IsPalindrome возвращает bool принимает параметр типа string и возвращает,
 * является ли переданная строка палиндромом
 * Палиндром - это слово или фраза, которые одинаково читаются слева направо и справа налево.
 * Пустая строка является палиндромом. */


bool IsPalindrome(const string& str) {

    int half_end_index = int(str.size() - 1 / 2);
    for (int i = 0; i < half_end_index; ++i) {
        if (str[i] != str[str.size() - 1 - i]) {
            return false;
        }
    }

    return true;
}


/* Напишите функцию UpdateIfGreater, которая принимает два целочисленных аргумента: first и second.
 * Если first оказался больше second, Ваша функция должна записывать в second значение параметра first.
 * При этом указанная функция не должна ничего возвращать,
 * а изменение параметра second должно быть видно на вызывающей стороне. */

void UpdateIfGreater(const int& first, int& second) {
    if (first > second) {
        second  = first;
    }
}


/* Реализуйте функцию vector<int> Reversed(const vector<int>& v),
 * возвращающую копию вектора v, в которой числа переставлены в обратном порядке.
 * Гарантируется, что вектор v имеет ненулевую длину. */


vector<int> Reversed(const vector<int>& v) {
    vector<int> b(v.size());
    for (int i = 0; i < v.size(); ++i) {
        b[i] = v[v.size() - 1 - i];
    }
    return b;
}



/* Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней.
 * Найдите номера дней (в нумерации с нуля) со значением температуры выше среднего арифметического за все N дней.
 * Гарантируется, что среднее арифметическое значений температуры является целым числом.
 * Формат ввода
 * Вводится число N, затем N неотрицательных целых чисел — значения температуры в 0-й, 1-й, ... (N−1)-й день.
 * Формат вывода
 * Первое число K — количество дней, значение температуры в которых выше среднего арифметического.
 * Затем K целых чисел — номера этих дней. */

void AverageTemperature() {
    int n, temperature, k;
    int average_temperature = 0;
    vector<int> temperatures, above_average_indices;

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> temperature;
        temperatures.push_back(temperature);
        average_temperature += temperature;
    }

    average_temperature /= n;

    for(int i = 0; i < n; i++) {
        if (temperatures[i] > average_temperature) {
            above_average_indices.push_back(i);
        }
    }

    cout << above_average_indices.size() << endl;
    for(int index : above_average_indices) {
        cout << index << " ";
    }
}


/* Слова называются анаграммами друг друга, если одно из них можно получить перестановкой букв в другом.
 * Например, слово «eat» можно получить перестановкой букв слова «tea»,
 * поэтому эти слова являются анаграммами друг друга.
 * Даны пары слов, проверьте для каждой из них, являются ли слова этой пары анаграммами друг друга.

Указание
Один из способов проверки того, являются ли слова анаграммами друг друга, заключается в следующем.
 Для каждого слова с помощью словаря подсчитаем, сколько раз в нём встречается каждая буква.
 Если для обоих слов эти словари равны (а это проверяется с помощью обычного оператора ==),
 то слова являются анаграммами друг друга, в противном случае не являются.
При этом построение такого словаря по слову удобно вынести в отдельную функцию BuildCharCounters.

Формат ввода
Сначала дано число пар слов N, затем в N строках содержатся пары слов, которые необходимо проверить.
 Гарантируется, что все слова состоят лишь из строчных латинских букв.

Формат вывода
Выведите N строк: для каждой введённой пары слов YES, если эти слова являются анаграммами, и NO в противном случае. */

map<char, int> BuildCharCounters(const string& word) {
    map<char, int> character_map;
    for (char character: word) {
        character_map[character]++;
    }
    return character_map;
}

void Anagrams() {
    int n;
    string word_1, word_2;
    string yes = "YES ";
    string no = "NO ";

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> word_1 >> word_2;
        if (BuildCharCounters(word_1) == BuildCharCounters(word_2)) {
            cout << yes;
        } else {
            cout << no;
        }

    }
}



/* Реализуйте справочник столиц стран.
 *
На вход программе поступают следующие запросы:
    CHANGE_CAPITAL country new_capital — изменение столицы страны country на new_capital,
        либо добавление такой страны с такой столицей, если раньше её не было.
    RENAME old_country_name new_country_name — переименование страны из old_country_name в new_country_name.
    ABOUT country — вывод столицы страны country.
    DUMP — вывод столиц всех стран.

Формат ввода
    В первой строке содержится количество запросов Q,
    в следующих Q строках — описания запросов. Все названия стран и столиц состоят лишь из латинских букв, цифр и символов подчёркивания.

Формат вывода
Выведите результат обработки каждого запроса:

В ответ на запрос CHANGE_CAPITAL country new_capital выведите
    Introduce new country country with capital new_capital, если страны country раньше не существовало;
    Country country hasn't changed its capital, если страна country до текущего момента имела столицу new_capital;
    Country country has changed its capital from old_capital to new_capital,
        если страна country до текущего момента имела столицу old_capital,
        название которой не совпадает с названием new_capital.

В ответ на запрос RENAME old_country_name new_country_name выведите
    Incorrect rename, skip, если новое название страны совпадает со старым,
        страна old_country_name не существует или страна new_country_name уже существует;
    Country old_country_name with capital capital has been renamed to new_country_name, если запрос корректен и страна имеет столицу capital.

В ответ на запрос ABOUT country выведите
    Country country doesn't exist, если страны с названием country не существует;

    Country country has capital capital, если страна country существует и имеет столицу capital.

В ответ на запрос DUMP выведите
    There are no countries in the world, если пока не было добавлено ни одной страны;
    последовательность пар вида country/capital, описывающую столицы всех стран, если в мире уже есть хотя бы одна страна.

 При выводе последовательности пары указанного вида необходимо упорядочить по названию страны и разделять между собой пробелом. */

void DirectoryOfCapitals() {
    int Q;
    string command;
    map<string, string> countries_capitals;

    cin >> Q;

    for (int i = 0; i < Q; ++i) {
        cin >> command;
        if (command == "CHANGE_CAPITAL") {
            string country, new_capital;
            cin >> country >> new_capital;

            if (countries_capitals.count(country) == 0) {
                cout << "Introduce new country " << country << " with capital " << new_capital << endl;
                countries_capitals[country] = new_capital;
            } else {
                if (countries_capitals[country] == new_capital) {
                    cout << "Country " << country << " hasn't changed its capital" << endl;
                } else {
                    cout << "Country "  << country << " has changed its capital from "
                        << countries_capitals[country] << " to " << new_capital << endl;
                    countries_capitals[country] = new_capital;
                }

            }
        } else if (command == "RENAME") {
            string old_country_name, new_country_name;
            cin >> old_country_name >> new_country_name;

            if (
                countries_capitals.count(old_country_name) == 0 ||
                countries_capitals.count(new_country_name) == 1 ||
                new_country_name == old_country_name
            ) {
                cout << "Incorrect rename, skip" << endl;
            } else {
                cout << "Country " << old_country_name << " with capital "
                     << countries_capitals[old_country_name] << " has been renamed to " << new_country_name << endl;
                countries_capitals[new_country_name] = countries_capitals[old_country_name];
                countries_capitals.erase(old_country_name);
            }
        } else if (command == "ABOUT") {
            string country;
            cin >> country;

            if (countries_capitals.count(country) == 0) {
                cout << "Country " << country << " doesn't exist" << endl;
            } else {
                cout << "Country " << country << " has capital " << countries_capitals[country] << endl;
            }
        } else if (command == "DUMP") {
            if (countries_capitals.empty()) {
                cout << "There are no countries in the world" << endl;
            } else {
                for (const auto& [country, capital]: countries_capitals) {
                    cout << country << "/" << capital << " ";
                }
                cout << endl;
            }

        }
    }
}



/* Дан набор строк. Найдите количество уникальных строк в этом наборе.

Формат ввода
    Сначала вводится количество строк N, затем — сами N строк, разделённые символом перевода строки.
    Все строки состоят лишь из латинских букв, цифр и символов подчёркивания.

Формат вывода
    Выведите единственное целое число — количество уникальных строк в данном наборе.
*/

void UniqueStringsNumber() {
    int n;
    string str;
    set<string> strings_set;

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> str;
        strings_set.insert(str);
    }

    cout << strings_set.size();
}


/* Напишите функцию BuildMapValuesSet, принимающую на вход словарь map<int, string> и
 * возвращающую множество значений этого словаря: */

set<string> BuildMapValuesSet(const map<int, string>& m) {
    set<string> resulting_set;
    for (const auto& [key, value]: m) {
        resulting_set.insert(value);
    }
    return resulting_set;
}


int main() {

    return 0;
}
