#pragma once

#include "date.h"
#include "event.h"

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>


struct Entry {
    Date date;
    std::string event;
};

std::ostream& operator <<(std::ostream& stream, const Entry& value);

std::istream& operator >>(std::istream& stream, Entry& value);


class Database {
public:
    void Add(const Date& date, const Event& event);

    void Print(std::ostream& stream) const;

    template <typename Predicate>
    int RemoveIf(Predicate predicate) {
        int events_removed_number = 0;
        for (auto& [date, events_vector]: events_order) {
//            auto memory_end_ = end(events_vector);
            for (auto event_iterator = begin(events_vector); event_iterator != end(events_vector); ) {
                if (predicate(date, *event_iterator)) {
                    events[date].erase(*event_iterator);
                    events_order[date].erase(event_iterator);
                    if (events[date].empty()) {
                        events.erase(date);
                        events_order.erase(date);
                    }
                    events_removed_number++;
                } else {
                    ++event_iterator;
                }
            }
        }
        return events_removed_number;
    }

    template <typename Predicate>
    std::vector<Entry> FindIf(Predicate predicate) {
        std::vector<Entry> entries;
        for (auto& [date, events_set]: events) {
            for (const Event& event: events_set) {
                if (predicate(date, event)) {
                    entries.push_back(Entry{date, event.value});
                }
            }
        }
        return entries;
    }

    Entry Last(const Date& date);

private:
    std::map<Date, std::set<Event>> events;
    std::map<Date, std::vector<Event>> events_order;
};