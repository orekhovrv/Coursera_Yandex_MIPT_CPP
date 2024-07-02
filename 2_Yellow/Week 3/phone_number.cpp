// Вам дан заголовочный файл phone_number.h, содержащий объявление класса PhoneNumber.
// При этом в комментариях описано поведение, которое ожидается от реализации этого класса.
// Пришлите cpp-файл с определениями методов класса PhoneNumber, которые реализуют описанное поведение.

#include <stdexcept>
//#include <iostream>
#include "phone_number.h"

using namespace std;


PhoneNumber::PhoneNumber(const string &international_number) {
    bool is_correct = true;

    if (international_number[0] != '+') {
        is_correct = false;
    }

    auto first_separator_position = international_number.find('-');
    if (first_separator_position == -1) {
          is_correct = false;
    }

    auto second_separator_position = international_number.find('-', first_separator_position + 1);
    if (second_separator_position == -1) {
        is_correct = false;
    }

    if (!is_correct) {
        throw invalid_argument("");
    }

    country_code_ = international_number.substr(1, first_separator_position - 1);
    city_code_ = international_number.substr(first_separator_position + 1, second_separator_position - first_separator_position - 1);
    local_number_ = international_number.substr(second_separator_position + 1);

}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return "+" + country_code_ + "-" +  city_code_ + "-" +  local_number_;
}

//int main () {
//    PhoneNumber number = PhoneNumber("+7-495-1112233");
//
//    cout << number.GetCountryCode() << " " << number.GetCityCode() << " " << number.GetLocalNumber();
//
//    return 0;
//}