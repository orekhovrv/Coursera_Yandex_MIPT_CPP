#include <iostream>
#include <numeric>

using namespace std;


// В первой части Вам надо реализовать класс Rational, который представляет собой рациональное число вида p/q,
// где p — целое, а q — натуральное и диапазоны возможных значений p, q таковы, что могут быть представлены типом int.
// При этом, класс Rational должен иметь следующий интерфейс:
// Класс Rational должен гарантировать, что p/q — это несократимая дробь.

//Список требований, предъявляемых к реализации интерфейса класса Rational:
//
//Конструктор по умолчанию должен создавать дробь с числителем 0 и знаменателем 1.
//
//При конструировании объека класса Rational с параметрами p и q должно выполняться сокращение дроби p/q (здесь вам может пригодиться решение задачи «Наибольший общий делитель»).
//
//Если дробь p/q отрицательная, то объект Rational(p, q) должен иметь отрицательный числитель и положительный знаменатель.
//
//Если дробь p/q положительная, то объект Rational(p, q) должен иметь положительные числитель и знаменатель (обратите внимание на случай Rational(-2, -3)).
//
//Если числитель дроби равен нулю, то знаменатель должен быть равен 1.
//
//Гарантируется, что ни в одном из тестов, на которых будет тестироваться ваша реализация, не будет знаменателя, равного нулю.


class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational(int new_numerator, int new_denominator) {
        numerator = new_numerator;
        denominator = new_denominator;
        normalize();
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

private:
    int numerator, denominator;

    void normalize() {
        normalize_signs();
        normalize_ratio();
    }

    void normalize_ratio() {
        if (numerator != 0) {
            int greatest_common_divisor = gcd(numerator, denominator);
            numerator /= greatest_common_divisor;
            denominator /= greatest_common_divisor;
        } else {
            denominator = 1;
        }
    }

    void normalize_signs() {
        if (denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
    }

};

int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}