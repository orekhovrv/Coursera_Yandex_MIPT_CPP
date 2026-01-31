#include <string>
#include <iostream>
#include <iomanip>


using namespace std;

class Date {
public:
    int year, month, day;
};

char delimiter = '-';

Date ParseDate(istringstream& stream) {

}

bool operator <(const Date& value_1, const Date& value_2) {
    return (value_1.year < value_2.year) ||
           (value_1.year == value_2.year && value_1.month < value_2.month)  ||
           (value_1.year == value_2.year && value_1.month == value_2.month && value_1.day < value_2.day);
}

ostream& operator <<(ostream& stream, const Date& value) {
    stream << setw(4) << setfill('0') << value.year <<
           delimiter << setw(2) << setfill('0') << value.month <<
           delimiter << setw(2) << setfill('0') << value.day;
    return stream;
}

void CheckDateValidity(const Date& value, const char& delimiter_1, const char& delimiter_2, const bool& is_parsed) {
    if (!is_parsed) {
        string input_value = to_string(value.year) + delimiter_1 +
                             to_string(value.month) + delimiter_2 + to_string(value.day);
        throw logic_error("Wrong date format: " + input_value);
    }

    if (value.month > 12 || 1 > value.month) {
        throw logic_error("Month value is invalid: " + to_string(value.month));
    } else if (value.day > 31 || 1 > value.day) {
        throw logic_error("Day value is invalid: " + to_string(value.day));
    }
}

istream& operator >>(istream& stream, Date& value) {
    bool is_parsed = bool(stream >> value.year);

    char delimiter_1 = char(stream.peek());
    is_parsed = is_parsed && delimiter_1 == delimiter;
    stream.ignore(1);

    is_parsed = is_parsed && stream >> value.month;

    char delimiter_2 = char(stream.peek());
    is_parsed = is_parsed && delimiter_2 == delimiter;
    stream.ignore(1);

    is_parsed = is_parsed && stream >> value.day;

    CheckDateValidity(value, delimiter_1, delimiter_2, is_parsed);

    return stream;
}