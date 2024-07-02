#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

/*
Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.

Считайте, что в каждый год может произойти не более одного изменения фамилии и не более одного изменения имени.
 При этом с течением времени могут открываться всё новые факты из прошлого человека,
 поэтому года́ в последовательных вызовах методов ChangeLastName и ChangeFirstName не обязаны возрастать.

Гарантируется, что все имена и фамилии непусты.

Строка, возвращаемая методом GetFullName,
 должна содержать разделённые одним пробелом имя и фамилию человека по состоянию на конец данного года.

Если к данному году не случилось ни одного изменения фамилии и имени, верните строку "Incognito".

Если к данному году случилось изменение фамилии, но не было ни одного изменения имени,
 верните "last_name with unknown first name".

Если к данному году случилось изменение имени, но не было ни одного изменения фамилии,
 верните "first_name with unknown last name".
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

    private:
        map<int, string> first_name_history, last_name_history;

        string GetFirstName(const int& year) {
            return GetLastValue(first_name_history, year);
        }

        string GetLastName(const int& year) {
            return GetLastValue(last_name_history, year);
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
};



int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}
