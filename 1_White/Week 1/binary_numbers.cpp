#include <iostream>
#include <vector>

using namespace std;


/* На вход дано целое положительное число N. Выведите его в двоичной системе счисления без ведущих нулей. */


int main() {
    int n, residual;
    vector<int> binary;
    bool is_leading_zero = true;

    cin >> n;

    while(n > 0) {
        residual = n % 2;
        binary.push_back(residual);
        n /= 2;
    }

    for (int index = binary.size() - 1; index >= 0; index--) {
        if (binary[index] != 0) {
            is_leading_zero = false;
        }
        if (!is_leading_zero) {
            cout << binary[index];
        }
    }

    return 0;
}
