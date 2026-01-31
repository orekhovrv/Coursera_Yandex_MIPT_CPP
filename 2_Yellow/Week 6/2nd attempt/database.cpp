#include <vector>
#include <map>
#include <set>
#include <iostream>
#include "date.cpp"
#include "event.cpp"


using namespace std;

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
