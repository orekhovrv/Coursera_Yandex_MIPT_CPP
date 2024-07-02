#include <numeric>
#include <iostream>
#include <vector>

using namespace std;


// Вставьте сюда реализацию класса Rational

class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational(int new_numerator, int new_denominator) {
        if (new_denominator == 0) {
            throw invalid_argument("Invalid argument");
        }

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
    if (value_2.Numerator() == 0) {
        throw domain_error("Division by zero");
    }
    vector<int> numerators_and_denominator = get_numerators_and_denominator(value_1, value_2);
    return Rational(value_1.Numerator() * value_2.Denominator(), value_1.Denominator() * value_2.Numerator());
}

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

bool operator <(const Rational& rational_1, const Rational& rational_2) {
    vector<int> numerators_and_denominator = get_numerators_and_denominator(rational_1, rational_2);
    return numerators_and_denominator[0] < numerators_and_denominator[1];
}


int main()
{
    Rational rational_1, rational_2;
    char operation;

    try {
        cin >> rational_1 >> operation >> rational_2;

        if (operation == '+')
        {
            cout << rational_1 + rational_2 << endl;
        } else if (operation == '-') {
            cout << rational_1 - rational_2 << endl;
        } else if (operation == '*') {
            cout << rational_1 * rational_2 << endl;
        } else if (operation == '/') {
            try {
                cout << rational_1 / rational_2 << endl;
            }  catch (domain_error& de) {
                cout << de.what();
            }
        }
    } catch (invalid_argument& error) {
        cout << error.what();
    }
    return 0;
}
