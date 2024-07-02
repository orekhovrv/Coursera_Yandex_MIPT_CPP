#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <iomanip>


using namespace std;


struct Date {
    int year, month, day;
};

char delimiter = '-';

bool operator <(const Date& value_1, const Date& value_2) {
    return (value_1.year < value_2.year) ||
        (value_1.year == value_2.year && value_1.month < value_2.month)  ||
        (value_1.year == value_2.year && value_1.month == value_2.month && value_1.day < value_2.day);
}

ostream& operator <<(ostream& stream, const Date& value) {
    stream << setw(4) << setfill('0') << value.year <<
           DELIMITER << setw(2) << setfill('0') << value.month <<
           DELIMITER << setw(2) << setfill('0') << value.day;
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
    is_parsed = is_parsed && delimiter_1 == DELIMITER;
    stream.ignore(1);

    is_parsed = is_parsed && stream >> value.month;

    char delimiter_2 = char(stream.peek());
    is_parsed = is_parsed && delimiter_2 == DELIMITER;
    stream.ignore(1);

    is_parsed = is_parsed && stream >> value.day;

    CheckDateValidity(value, delimiter_1, delimiter_2, is_parsed);

    return stream;
}


struct Event {
    string value;
};

bool operator <(const Event& value_1, const Event& value_2) {
    return value_1.value < value_2.value;
}

ostream& operator <<(ostream& stream, const Event& value) {
    stream << value.value;
    return stream;
}

istream& operator >>(istream& stream, Event& value) {
    string event_value;
    stream >> event_value;
    auto x = event_value.find_first_not_of(' ');
    value.value = x != string::npos ? event_value.substr(x, event_value.size() - x) : "";
    return stream;
}


class Database {
public:

    void Add(const Date& date, const Event& event) {
        events[date].insert(event);
    }

    void Del(const Date& date, const Event& event) {
        if (events.count(date) > 0 && events[date].count(event) > 0) {
            events[date].erase(event);
            cout << "Deleted successfully" << endl;
        } else {
            cout << "Event not found" << endl;
        }
    }

    void Del(const Date& date) {
        int deleted_events_number = 0;
        if (events.count(date) > 0) {
            deleted_events_number = int(events[date].size());
        }
        events.erase(date);
        cout << "Deleted " << deleted_events_number <<" events" << endl;
    }

    void Find(const Date& date) const {
        for (const Event& event: events.at(date)) {
            cout << event << endl;
        }
    }

    void Print() const {
        for (auto& [date, events_set]: events) {
            for (const Event& event: events_set) {
                cout << date << " " << event << endl;
            }
        }
    }

private:
    map<Date, set<Event>> events;
};



int main() {
    Database database;
    string command_line;

    while (getline(cin, command_line)) {

        stringstream command_line_stream(command_line);
        string command;
        Date date{};
        Event event;

        command_line_stream >> command;

        try {
            if (command == "Add") {
                command_line_stream >> date >> event;
                database.Add(date, event);
            } else if (command == "Del") {
                command_line_stream >> date;

                if (!command_line_stream.eof()) {
                    command_line_stream >> event;
                    database.Del(date, event);
                } else {
                    database.Del(date);
                }
            } else if (command == "Find") {
                command_line_stream >> date;
                database.Find(date);
            } else if (command == "Print") {
                database.Print();
            } else if (command.empty()) {
            } else {
                throw logic_error("Unknown command: " + command);
            }
        } catch(const logic_error& error) {
            cout << error.what() << endl;
            return 0;
        }
    }

    return 0;
}