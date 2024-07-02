#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

/*
Дополните класс из предыдущей задачи «Имена и фамилии — 1» методом GetFullNameWithHistory:

В отличие от метода GetFullName,
 метод GetFullNameWithHistory должен вернуть не только последние имя и фамилию к концу данного года,
 но ещё и все предыдущие имена и фамилии в обратном хронологическом порядке.
 Если текущие факты говорят о том, что человек два раза подряд изменил фамилию или имя на одно и то же,
 второе изменение при формировании истории нужно игнорировать.
*/


class Person {

public:

    void ChangeFirstName(int year, const string& first_name) {
        // добавить факт изменения имени на first_name в год year
        first_name_history[year] = first_name;
    }

    void ChangeLastName(int year, const string& last_name) {
        // добавить факт изменения фамилии на last_name в год year
        last_name_history[year] = last_name;
    }

    string GetFullName(int year) {
        // получить имя и фамилию по состоянию на конец года year

        string first_name = GetFirstName(year);
        string last_name = GetLastName(year);

        return BuildFullName(first_name, last_name);
    }

    string GetFullNameWithHistory(int year) {
        // получить все имена и фамилии по состоянию на конец года year

        string first_name = GetFirstNameWithHistory(year);
        string last_name = GetLastNameWithHistory(year);

        return BuildFullName(first_name, last_name);
    }

private:
    map<int, string> first_name_history, last_name_history;

    string GetFirstName(const int& year) {
        return GetLastValue(first_name_history, year);
    }

    string GetLastName(const int& year) {
        return GetLastValue(last_name_history, year);
    }

    string GetFirstNameWithHistory(const int& year) {
        return BuildNameWithHistory(GetHistory(first_name_history, year));
    }

    string GetLastNameWithHistory(const int& year) {
        return BuildNameWithHistory(GetHistory(last_name_history, year));
    }

    static string GetLastValue(const map<int, string>& value_history, const int& year) {
        if (value_history.empty()) {
            return "";
        } else {
            string last_value;
            for (const auto& [change_year, value]: value_history) {
                if (change_year > year) {
                    break;
                }
                last_value = value;
            }
            return last_value;
        }
    }

    static vector<string> GetHistory(const map<int, string>& value_history, const int& year) {
        vector<string> history;
        for (const auto& [change_year, value]: value_history) {
            if (change_year > year) {
                break;
            }
            if (history.empty() || history.back() != value) {
                history.push_back(value);
            }
        }
        return history;
    }

    static string BuildNameWithHistory(vector<string> history) {

        if (history.empty()) {
            return "";
        }

        reverse(begin(history), end(history));
        
        string name = history[0];

        for (int i = 1; i < history.size(); ++i) {
            if (i == 1) {
                name += " (";
            } else {
                name += ", ";
            }
            name += history[i];
        }

        if (history.size() > 1) {
            name += ")";
        }

        return name;
    }

    static string BuildFullName(const string& first_name, const string& last_name) {
        if (first_name.empty() && last_name.empty()) {
            return "Incognito";
        } else if (first_name.empty()) {
            return last_name + " with unknown first name" ;
        } else if (last_name.empty()) {
            return first_name + " with unknown last name";
        } else {
            return first_name + " " + last_name;
        }
    }
};



void main_1() {
    Person person;

    person.ChangeFirstName(1900, "Eugene");
    person.ChangeLastName(1900, "Sokolov");
    person.ChangeLastName(1910, "Sokolov");
    person.ChangeFirstName(1920, "Evgeny");
    person.ChangeLastName(1930, "Sokolov");
    cout << person.GetFullNameWithHistory(1940) << endl;
}

void main_2() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;

    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;

    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;
}

void main_3() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeFirstName(1965, "Appolinaria");

    person.ChangeLastName(1965, "Sergeeva");
    person.ChangeLastName(1965, "Volkova");
    person.ChangeLastName(1965, "Volkova-Sergeeva");

    for (int year : {1964, 1965, 1966}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }
}

int main() {

    main_3();

    return 0;
}
