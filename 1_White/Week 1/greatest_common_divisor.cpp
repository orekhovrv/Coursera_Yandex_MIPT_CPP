#include <iostream>

using namespace std;


/* В stdin даны два натуральных числа. Выведите в stdout их наибольший общий делитель. */


void euclid() {
    int a, b;

    cin >> a >> b;

    while(a > 0 && b > 0) {
        if (a > b) {
            a = a % b;
        } else {
            b = b % a;
        }
    }
    cout << a + b;
};


void brute_force() {
    int a, b, c;

    cin >> a >> b;
    if (b < a) {
        c = a;
        a = b;
        b = c;
    }

    if (b % a == 0) {
        cout << a;
        return;
    }

    for (int number = a / 2; number >= 0; number--) {
        if ((a % number) == 0 && (b % number) == 0) {
            cout << number;
            return;
        }
    }
};


int main() {

    brute_force();
//    euclid();

    return 0;
}
