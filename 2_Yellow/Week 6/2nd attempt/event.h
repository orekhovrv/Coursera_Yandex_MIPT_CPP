#pragma once

#include <iostream>
#include <string>


struct Event {
    std::string value;
};

Event ParseEvent(std::istream& stream);

bool operator <(const Event& value_1, const Event& value_2);

std::ostream& operator <<(std::ostream& stream, const Event& value);

std::istream& operator >>(std::istream& stream, Event& value);

bool operator !=(const Event& e1, const Event& e2);
