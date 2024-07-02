#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;


/*
Дополните класс Person из задачи «Имена и фамилии — 2» конструктором,
 позволяющим задать имя и фамилию человека при рождении, а также сам год рождения.
 Класс не должен иметь конструктора по умолчанию.

При получении на вход года, который меньше года рождения:

    методы GetFullName и GetFullNameWithHistory должны отдавать "No person";

    методы ChangeFirstName и ChangeLastName должны игнорировать запрос.

Кроме того, необходимо объявить константными все методы, которые по сути ими являются.
 */

class Person {

public:

    Person(const string& birth_first_name, const string& birth_last_name, int new_birth_year) {
        ChangeFirstName(new_birth_year, birth_first_name);
        ChangeLastName(new_birth_year, birth_last_name);
        birth_year = new_birth_year;
    }

    void ChangeFirstName(int year, const string& first_name) {
        // добавить факт изменения имени на first_name в год year
        first_name_history[year] = first_name;
    }

    void ChangeLastName(int year, const string& last_name) {
        // добавить факт изменения фамилии на last_name в год year
        last_name_history[year] = last_name;
    }

    string GetFullName(int year) const {
        // получить имя и фамилию по состоянию на конец года year

        string birth_year_error_message = CheckBirthYear(year);
        if (!birth_year_error_message.empty()) {
            return birth_year_error_message;
        };

        string first_name = GetFirstName(year);
        string last_name = GetLastName(year);

        return BuildFullName(first_name, last_name);
    }

    string GetFullNameWithHistory(int year) const {
        // получить все имена и фамилии по состоянию на конец года year

        string birth_year_error_message = CheckBirthYear(year);
        if (!birth_year_error_message.empty()) {
            return birth_year_error_message;
        };

        string first_name = GetFirstNameWithHistory(year);
        string last_name = GetLastNameWithHistory(year);

        return BuildFullName(first_name, last_name);
    }

private:
    map<int, string> first_name_history, last_name_history;
    int birth_year;

    string GetFirstName(int year) const {
        return GetLastValue(first_name_history, year);
    }

    string GetLastName(int year) const {
        return GetLastValue(last_name_history, year);
    }

    string GetFirstNameWithHistory(int year) const {
        return BuildNameWithHistory(GetHistory(first_name_history, year));
    }

    string GetLastNameWithHistory(int year) const {
        return BuildNameWithHistory(GetHistory(last_name_history, year));
    }

    string CheckBirthYear(int year) const {
        if (year < birth_year) {
            return "No person";
        } else {
            return "";
        }
    }

    static string GetLastValue(const map<int, string>& value_history, int year) {
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

    static vector<string> GetHistory(const map<int, string>& value_history, int year) {
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
//        if (first_name.empty() && last_name.empty()) {
//            return "Incognito";
//        } else if (first_name.empty()) {
//            return last_name + " with unknown first name" ;
//        } else if (last_name.empty()) {
//            return first_name + " with unknown last name";
//        } else {
//            return first_name + " " + last_name;
//        }
        return first_name + " " + last_name;
    }
};



int main() {
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}
