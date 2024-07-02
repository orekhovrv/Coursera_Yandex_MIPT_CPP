#include <iostream>
//#include <set>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
Реализуйте класс, поддерживающий набор строк в отсортированном порядке. Класс должен содержать два публичных метода:
 */

class SortedStrings {
    public:

        void AddString(const string& s) {
            // добавить строку s в набор
            strings.push_back(s);
        }

        vector<string> GetSortedStrings() {
            // получить набор из всех добавленных строк в отсортированном порядке
            sort(begin(strings), end(strings));
            return strings;
        }

    private:
        // приватные поля

        vector<string> strings;
};


//void PrintSortedStrings(SortedStrings& strings) {
//    for (const string& s : strings.GetSortedStrings()) {
//        cout << s << " ";
//    }
//    cout << endl;
//}
//
//int main() {
//    SortedStrings strings;
//
//    strings.AddString("first");
//    strings.AddString("third");
//    strings.AddString("second");
//    PrintSortedStrings(strings);
//
//    strings.AddString("second");
//    PrintSortedStrings(strings);
//
//    return 0;
//}
