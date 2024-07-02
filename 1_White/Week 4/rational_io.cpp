#include <iostream>
#include <numeric>
#include <vector>
#include <sstream>

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

Rational operator *(const Rational& value_1, const Rational& value_2) {
    return Rational(value_1.Numerator() * value_2.Numerator(), value_1.Denominator() * value_2.Denominator());
}

Rational operator /(const Rational& value_1, const Rational& value_2) {
    vector<int> numerators_and_denominator = get_numerators_and_denominator(value_1, value_2);
    return Rational(value_1.Numerator() * value_2.Denominator(), value_1.Denominator() * value_2.Numerator());
}



// Implement << and >> operators for Rational class

istream& operator >>(istream& stream, Rational& rational) {
    int numerator, denominator;
    char delimiter;

    if (stream) {
        stream >> numerator >> delimiter >> denominator;
        if (stream && delimiter == '/') {
            rational = Rational(numerator, denominator);
        }
    }

    return stream;
}

ostream& operator <<(ostream& stream, const Rational& rational) {
    stream << rational.Numerator() << "/" << rational.Denominator();
    return stream;
}


int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct) {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                 << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }

    {
        istringstream input("2/4/6/8");
        Rational r1;
        input >> r1;
        bool correct = r1 == Rational(1, 2);
        if (!correct) {
            cout << "Multiple-slashed number sequence value read incorrectly: " << r1 << endl;
            return 7;
        }
    }

    cout << "OK" << endl;
    return 0;
}
