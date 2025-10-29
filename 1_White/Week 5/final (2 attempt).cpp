/*
Необходимо написать программу на С++, которая реализует работу с простой базой данных (сокращённо «БД»). Программа будет общаться с пользователем через стандартный ввод и вывод (потоки stdin и stdout).

Будем хранить в нашей БД пары вида: дата, событие. Определим дату как строку вида Год-Месяц-День, где Год, Месяц и День — целые числа.

Событие определим как строку из произвольных печатных символов без разделителей внутри (пробелов, табуляций и пр.). Событие не может быть пустой строкой. В одну и ту же дату может произойти много разных событий, БД должна суметь их все сохранить. Одинаковые события, произошедшие в один и тот же день, сохранять не нужно: достаточно сохранить только одно из них.

Наша БД должна понимать определённые команды, чтобы с ней можно было взаимодействовать:

6
- добавление события:                        Add Дата Событие
- удаление события:                          Del Дата Событие
- удаление всех событий за конкретную дату:  Del Дата
- поиск событий за конкретную дату:          Find Дата
- печать всех событий за все даты:           Print

Все команды, даты и события при вводе разделены пробелами. Команды считываются из стандартного ввода. В одной строке может быть ровно одна команда, но можно ввести несколько команд в несколько строк. На вход также могут поступать пустые строки — их следует игнорировать и продолжать обработку новых команд в последующих строках.

Добавление события (Add Дата Событие)
При добавлении события БД должна его запомнить и затем показывать его при поиске (командой Find) или печати (командой Print). Если указанное событие для данной даты уже существует, повторное его добавление нужно игнорировать. В случае корректного ввода (см. раздел «Обработка ошибок ввода») программа ничего не должна выводить на экран.

Удаление события (Del Дата Событие)
Команда должна удалить добавленное ранее событие с указанным именем в указанную дату, если оно существует. Если событие найдено и удалено, программа должна вывести строку «Deleted successfully» (без кавычек). Если событие в указанную дату не найдено, программа должна вывести строку «Event not found» (без кавычек).

Удаление нескольких событий (Del Дата)
Команда удаляет все ранее добавленные события за указанную дату. Программа всегда должна выводить строку вида «Deleted N events», где N — это количество всех найденных и удалённых событий. N может быть равно нулю, если в указанную дату не было ни одного события.

Поиск событий (Find Дата)
Найти и распечатать ранее добавленные события в указанную дату. Программа должна вывести на печать только сами события, по одному на строке. События должны быть отсортированы по возрастанию в порядке сравнения строк между собой (тип string).

Печать всех событий (Print)
С помощью этой команды можно показать полное содержимое нашей БД. Программа должна вывести на печать все пары Дата Событие по одной на строке. Все пары должны быть отсортированы по дате, а события в рамках одной даты должны быть отсортированы по возрастанию в порядке сравнения строк между собой (тип string). Даты должны быть отформатированы специальным образом: ГГГГ-ММ-ДД, где Г, М, Д — это цифры чисел года, месяца и дня соответственно. Если какое-то число имеет меньше разрядов, то оно должно дополняться нулями, например, 0001-01-01 — первое января первого года. Вам не понадобится выводить дату с отрицательным значением года.

Обработка ошибок ввода
Ввод в этой задаче не всегда корректен: некоторые ошибки ввода ваша программа должна корректно обрабатывать.
*/

#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

using namespace std;

struct Date {
    int year, month, day;
};

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.year == rhs.year) {
        if (lhs.month == rhs.month) {
            return lhs.day < rhs.day;
        } else {
            return lhs.month < rhs.month;
        }
    } else {
        return lhs.year < rhs.year;
    }
}

ostream& operator<<(ostream& stream, const Date& date) {
    stream << setw(4) << setfill('0') << date.year <<
           '-' << setw(2) << date.month <<
           '-' << setw(2) << date.day;
    return stream;
}

istream& operator>>(istream& stream, Date& date) {
    string input_date;
    getline(stream, input_date);
    stringstream input_date_stream(input_date);

    char delimiter;

    input_date_stream >> date.year;

    stream >> delimiter;
    if (delimiter != '-') {
        throw logic_error("Wrong date format: " + input_date);
    }

    stream >> date.month;
    if (date.month < 1 || date.month > 12) {
        throw logic_error("Month value is invalid: " + to_string(date.month));
    }

    stream >> delimiter;
    if (delimiter != '-') {
        throw logic_error("Wrong date format: " + input_date);
    }

    stream >> date.day;
    if (date.day < 1 || date.month > 31) {
        throw logic_error("Day value is invalid: " + to_string(date.day));
    }

    return stream;
}

class Database {
public:
    void addEvent(const Date& date, const string& event){
        events[date].insert(event);
    }

    void deleteEvent(const Date& date, const string& event) {
        if (events.count(date) && events[date].count(event)) {
            events[date].erase(event);
            cout << "Deleted successfully" << endl;
        }
    }

    void  deleteDate(const Date& date) {
        if (events.count(date)) {
            size_t events_count = events[date].size();
            events.erase(date);
            cout << "Deleted " << events_count << " events" << endl;
        }
    }

    void find(const Date& date) const {
        for (const string& event: events.at(date)) {
            cout << event << endl;
        }
    }

    void print() const {
        for (auto const& [date, date_events] : events) {
            for (auto const& event : date_events) {
                cout << date << " " << event << endl;
            }
        }
    }

private:
    map<Date, set<string>> events;

};

int main() {
    Database db;

    string command_line;
    while (getline(cin, command_line)) {
        stringstream command_line_stream(command_line);
        string command;
        Date date{};
        string event;

        command_line_stream >> command;
        command_line_stream >> date;
        command_line_stream >> event;

        try {
            if (command == "Add") {
                db.addEvent(date, event);
            } else if (command == "Del") {
                if (!event.empty()) {
                    db.deleteEvent(date, event);
                } else {
                    db.deleteDate(date);
                }
            } else if (command == "Find") {
                db.find(date);
            } else if (command == "Print") {
                db.print();
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