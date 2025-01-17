#include <iomanip>
#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

// Реализуйте этот макрос, а также необходимые операторы для классов Date и Time
#define UPDATE_FIELD(ticket, field, values) {\
    auto it = values.find(#field); \
    if (it != values.end()) {                \
        istringstream value_tring_stream(it->second);                    \
        value_tring_stream >> ticket.field; \
    }                                        \
} \



bool operator ==(const Date& v1, const Date& v2) {
    return v1.year == v2.year && v1.month == v2.month && v1.day == v2.day;
}

ostream& operator <<(ostream& stream, const Date& value) {
    stream << setw(4) << setfill('0') << value.year <<
           '-' << setw(2) << setfill('0') << value.month <<
           '-' << setw(2) << setfill('0') << value.day;
    return stream;
}


bool operator ==(const Time v1, const Time& v2) {
    return v1.hours == v2.hours && v1.minutes == v2.minutes;
}

ostream& operator <<(ostream& stream, const Time& value) {
    stream << setw(2) << setfill('0') << value.hours <<
           ':' << setw(2) << setfill('0') << value.minutes;
    return stream;
}

istream& operator>>(istream& is, Date& value) {
    is >> value.year;
    is.ignore(1);
    is >> value.month;
    is.ignore(1);
    is >> value.day;
    return is;
}

istream& operator>>(istream& is, Time& value) {
    is >> value.hours;
    is.ignore(1);
    is >> value.minutes;
    return is;
}


void TestUpdate() {
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
        {"departure_date", "2018-2-28"},
        {"departure_time", "17:40"},
    };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
        {"price", "12550"},
        {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
