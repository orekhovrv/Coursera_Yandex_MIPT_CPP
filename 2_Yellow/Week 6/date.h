#pragma once

#include <iostream>

struct Date {
    int year, month, day;
};


Date ParseDate(std::istream& stream);

bool operator == (const Date& lhs, const Date& rhs);
bool operator != (const Date& lhs, const Date& rhs);
bool operator < (const Date& lhs, const Date& rhs);
bool operator <= (const Date& lhs, const Date& rhs);
bool operator > (const Date& lhs, const Date& rhs);
bool operator >= (const Date& lhs, const Date& rhs);


std::ostream& operator <<(std::ostream& stream, const Date& value);

std::istream& operator >>(std::istream& stream, Date& value);

void CheckDateValidity(const Date& value, const char& delimiter_1, const char& delimiter_2, const bool& is_parsed);

