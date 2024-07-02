#include <iostream>
#include <string>

using namespace std;


/* Дана строка. Найдите в этой строке второе вхождение буквы f и выведите  индекс этого вхождения.
 * Если буква f в данной строке встречается только  один раз, выведите число -1, а если не встречается ни разу, выведите  число -2.
 * Индексы нумеруются с нуля. */


int main() {
    string str;
    char letter = 'f';

    cin >> str;

    int counter = 0;
    for (int index = 0; index < str.size(); ++index) {
        if (str[index] == letter) {
            counter++;
        }
        if (counter == 2) {
            cout << index;
            return 0;
        }
    }

    if (counter == 1) {
        cout << -1;
    } else if (counter == 0) {
        cout << -2;
    }

    return 0;
}
