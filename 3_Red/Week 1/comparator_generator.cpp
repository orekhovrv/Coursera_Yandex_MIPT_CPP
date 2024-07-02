#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>


using namespace std;

// Давайте представим, что вы разрабатываете инновационный сервис поиска авиабилетов AviaScanner. В вашем сервисе авиабилет представляется в виде структуры
// В данный момент вы работаете над функцией сортировки результатов поиска.
// Пользователь вводит свой запрос и получает список подходящих билетов.
// Дальше он может задавать параметры сортировки этого списка.
// Например, сначала по цене, затем по времени вылета и, наконец, по аэропорту прилёта.


struct Date {
    int year, month, day;
};

struct Time {
    int hours, minutes;
};

struct AirlineTicket {
    string from;
    string to;
    string airline;
    Date departure_date;
    Time departure_time;
    Date arrival_date;
    Time arrival_time;
    uint64_t price;
};

void SortTickets(vector<AirlineTicket>& tixs) {
    stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
        return lhs.to < rhs.to;
    });
    stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
        return lhs.departure_time < rhs.departure_time;
    });
    stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
        return lhs.price < rhs.price;
    });
}

void SortTickets2(vector<AirlineTicket>& tixs) {
    stable_sort(begin(tixs), end(tixs), SORT_BY(to));
    stable_sort(begin(tixs), end(tixs), SORT_BY(departure_time));
    stable_sort(begin(tixs), end(tixs), SORT_BY(price));
}