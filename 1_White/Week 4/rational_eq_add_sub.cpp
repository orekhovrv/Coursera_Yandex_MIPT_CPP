#include <iostream>
#include <numeric>
#include <vector>

using namespace std;



class Rational {
    // Вставьте сюда реализацию класса Rational из первой части
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

// Реализуйте для класса Rational операторы ==, + и -

bool operator ==(const Rational& value_1, const Rational& value_2) {
    return (value_1.Denominator() == value_2.Denominator()) && (value_1.Numerator() == value_2.Numerator());
}

vector<int> get_numerators_and_denominator(const Rational& value_1, const Rational& value_2) {
    int denominator = lcm(value_1.Denominator(), value_2.Denominator());
    int numerator_1 = denominator / value_1.Denominator() * value_1.Numerator();
    int numerator_2 = denominator / value_2.Denominator() * value_2.Numerator();
    return {numerator_1, numerator_2, denominator};
}

Rational operator +(const Rational& value_1, const Rational& value_2) {
    vector<int> numerators_and_denominator = get_numerators_and_denominator(value_1, value_2);
    return Rational(numerators_and_denominator[0] + numerators_and_denominator[1], numerators_and_denominator[2]);
}

Rational operator -(const Rational& value_1, const Rational& value_2) {
    vector<int> numerators_and_denominator = get_numerators_and_denominator(value_1, value_2);
    return Rational(numerators_and_denominator[0] - numerators_and_denominator[1], numerators_and_denominator[2]);
}




int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
