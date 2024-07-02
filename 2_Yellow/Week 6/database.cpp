#include "database.h"
#include "date.h"

#include <iostream>


using namespace std;


std::ostream& operator <<(std::ostream& stream, const Entry& entry) {
    stream << entry.date << " " << entry.event;
    return stream;
}

void Database::Add(const Date& date, const Event& event) {
    if (events[date].insert(event).second) {
        events_order[date].push_back(event);
    }
}

void Database::Print(std::ostream& stream) const {
    for (auto& [date, events_set]: events) {
        for (const Event& event: events_set) {
            stream << date << " " << event << endl;
        }
    }
}

Entry Database::Last(const Date& date) {
    auto lower_bound = events_order.lower_bound(date);
    if (lower_bound == events_order.begin()) {
        throw invalid_argument("");
    } else {
        --lower_bound;
        return {lower_bound->first, lower_bound->second.back().value};
    }
}
