#include <numeric>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;


// Вставьте сюда реализацию класса Rational из первой части
// Вставьте сюда реализацию operator == для класса Rational из второй части

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



// Реализуйте для класса Rational оператор(ы), необходимые для использования его
// в качестве ключа map'а и элемента set'а

bool operator <(const Rational& rational_1, const Rational& rational_2) {
    vector<int> numerators_and_denominator = get_numerators_and_denominator(rational_1, rational_2);
    return numerators_and_denominator[0] < numerators_and_denominator[1];
}


int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
