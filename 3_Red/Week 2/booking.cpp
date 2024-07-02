#include <iostream>
#include <cstdint>
#include <map>
#include <queue>
#include <limits>

using namespace std;

// Ваша программа должна обрабатывать следующие события:
//BOOK time hotel_name client_id room_count — забронировать клиентом client_id room_count номеров в отеле hotel_name  в момент времени time.
//CLIENTS hotel_name — вывести количество различных клиентов,
// бронировавших номера в отеле hotel_name  за последние сутки относительно последнего события бронирования в системе:
// current_time − 86400 < time ⩽ current_time, где 86400 — количество секунд в сутках.
// Обратите внимание, бронирование с временной меткой current_time − 86400 учитываться не должно.
//ROOMS hotel_name — вывести количество номеров, забронированных в отеле hotel_name  за последние сутки относительно последнего события бронирования в системе.
// Работа команды определяется образом, аналогичным определению работы команды CLIENTS.

//Формат входных данных
//В первой строке вводится количество запросов Q — натуральное число, не превосходящее 10^5. В следующих Q строках в соответствии с описанным выше форматом вводятся запросы. Гарантируется, что:
//time — целое число в диапазоне от −10^18 до 10^18 и не убывает от события к событию.
//hotel_name — строка из латинских букв и цифр, имеющая длину не более 12 символов.
//client_id — натуральное число, не превосходящее 10^9.
//room_count — целое положительное число, не превосходящее 1000.

//Формат выходных данных
//Для каждого запроса CLIENTS и ROOMS выведите единственное целое число — ответ на запрос. Если указанный в запросе отель пока не имеет ни одного бронирования, выведите 0.


struct Booking {
public:
    Booking(const int64_t& time_, const int& client_id_, const int& room_count_) :
        time(time_), client_id(client_id_), room_count(room_count_) {}

    const int64_t time;
    const int client_id, room_count;
};

class Hotel {
public:
    Hotel() = default;

    void AddBooking(const int64_t& time, const int& client_id, const int& room_count) {
        bookings.emplace(time, client_id, room_count);
        booked_rooms_number += room_count;
        client_bookings_number[client_id]++;
    }

    void CleanBookings(const int64_t& time) {
        while(!bookings.empty() && bookings.front().time <= time - 86400) {
            Booking& booking = bookings.front();
            booked_rooms_number -= booking.room_count;
            if (--client_bookings_number[booking.client_id] == 0) {
                client_bookings_number.erase(booking.client_id);
            }
            bookings.pop();
        }
    }

    int GetClientCount() {
        return client_bookings_number.size();
    }

    int GetRoomCount() const {
        return booked_rooms_number;
    }


private:
    queue<Booking> bookings;
    int booked_rooms_number = 0;
    map<int, int> client_bookings_number;
};

class HotelManager {
public:
    HotelManager() = default;

    void Book(const int64_t& time, const string& hotel_name, const int& client_id, const int& room_count) {
        // забронировать клиентом client_id room_count номеров в отеле hotel_name  в момент времени time.
        CleanBookings(time);
//        SetCurrentTime(time);
        AddBooking(time, hotel_name, client_id, room_count);
    }

    int GetClientCount(const string& hotel_name) {
        // вывести количество различных клиентов,
        // бронировавших номера в отеле hotel_name  за последние сутки относительно последнего события бронирования в системе:
        return hotels[hotel_name].GetClientCount();
    }

    int GetRoomCount(const string& hotel_name) {
        // вывести количество номеров, забронированных в отеле hotel_name  за последние сутки относительно последнего события бронирования в системе.
        // Работа команды определяется образом, аналогичным определению работы команды CLIENTS.
        return hotels[hotel_name].GetRoomCount();
    }

private:
//    int64_t current_time = numeric_limits<int64_t>::min();
    map<string, Hotel> hotels;

//    void SetCurrentTime(const int64_t& time) {
//        current_time = time;
//        CleanBookings(time);
//    }

    void CleanBookings(const int64_t& time) {
        for (auto& [hotel_name, hotel]: hotels) {
            hotel.CleanBookings(time);
        }
    }

    void AddBooking(const int64_t& time, const string& hotel_name, const int& client_id, const int& room_count) {
        hotels[hotel_name].AddBooking(time, client_id, room_count);


//        if (hotels.count(hotel_name)) {
//            hotels[hotel_name].AddBooking();
//        } else {
//            hotels[hotel_name] = Hotel();
//        }
    }

//    bool IsLastDay(int64_t time) const {
//        return (current_time - 86400) < time <= current_time;
//    }

};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    HotelManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            int64_t time;
            cin >> time;
            string hotel_name;
            cin >> hotel_name;
            int client_id, room_count;
            cin >> client_id >> room_count;
            manager.Book(time, hotel_name, client_id, room_count);
        } else {
            string hotel_name;
            cin >> hotel_name;
            if (query_type == "CLIENTS") {
                cout << manager.GetClientCount(hotel_name) << "\n";
            } else if (query_type == "ROOMS") {
                cout << manager.GetRoomCount(hotel_name) << "\n";
            }
        }
    }

    return 0;
}