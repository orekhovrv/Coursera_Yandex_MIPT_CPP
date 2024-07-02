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


// Вставьте сюда реализацию operator == для класса Rational из второй части

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


// Реализуйте для класса Rational операторы * и /

Rational operator *(const Rational& value_1, const Rational& value_2) {
    return Rational(value_1.Numerator() * value_2.Numerator(), value_1.Denominator() * value_2.Denominator());
}

Rational operator /(const Rational& value_1, const Rational& value_2) {
    vector<int> numerators_and_denominator = get_numerators_and_denominator(value_1, value_2);
    return Rational(value_1.Numerator() * value_2.Denominator(), value_1.Denominator() * value_2.Numerator());
}



int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}
