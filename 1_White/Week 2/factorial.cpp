#include <iostream>

using namespace std;


/* Напишите функцию, которая называется Factorial возвращает int принимает int и возвращает факториал своего аргумента.
 Гарантируется, что аргумент функции по модулю не превышает 10.
 Для отрицательных аргументов функция должна возвращать 1.
 */

int Factorial(int value) {
    if (value <= 0) {
        return 1;
    }

    int result = 1;
    for (int i = 2; i <= value; ++i) {
        result *= i;
    }
    return result;
}


//int main() {
//    int value;
//
//    cin >> value;
//    cout << Factorial(value);
//
//    return 0;
//}
