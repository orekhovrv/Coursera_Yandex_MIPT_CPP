#include <string>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

/*
Реализуйте систему хранения автобусных маршрутов. Вам нужно обрабатывать следующие запросы:

    NEW_BUS bus stop_count stop1 stop2 ...
    — добавить маршрут автобуса с названием bus и stop_count остановками с названиями stop1, stop2, ...

    BUSES_FOR_STOP stop
    — вывести названия всех маршрутов автобуса, проходящих через остановку stop.

    STOPS_FOR_BUS bus
    — вывести названия всех остановок маршрута bus со списком автобусов, на которые можно пересесть на каждой из остановок.

    ALL_BUSES
    — вывести список всех маршрутов с остановками.

Формат ввода
    В первой строке ввода содержится количество запросов Q, затем в Q строках следуют описания запросов.
    Гарантируется, что все названия маршрутов и остановок состоят лишь из латинских букв, цифр и знаков подчёркивания.
    Для каждого запроса NEW_BUS bus stop_count stop1 stop2 ... гарантируется,
     что маршрут bus отсутствует, количество остановок больше 0,
     а после числа stop_count следует именно такое количество названий остановок,
     причём все названия в каждом списке различны.

Формат вывода
    Для каждого запроса, кроме NEW_BUS, выведите соответствующий ответ на него:

    На запрос BUSES_FOR_STOP stop выведите через пробел список автобусов,
     проезжающих через эту остановку, в том порядке, в котором они создавались командами NEW_BUS.
     Если остановка stop не существует, выведите No stop.

    На запрос STOPS_FOR_BUS bus выведите описания остановок маршрута bus в отдельных строках в том порядке,
     в котором они были заданы в соответствующей команде NEW_BUS.
     Описание каждой остановки stop должно иметь вид Stop stop: bus1 bus2 ..., где bus1 bus2 ...
     — список автобусов, проезжающих через остановку stop, в порядке, в котором они создавались командами NEW_BUS,
     за исключением исходного маршрута bus. Если через остановку stop не проезжает ни один автобус, кроме bus,
     вместо списка автобусов для неё выведите no interchange.
     Если маршрут bus не существует, выведите No bus.

    На запрос ALL_BUSES выведите описания всех автобусов в алфавитном порядке.
     Описание каждого маршрута bus должно иметь вид Bus bus: stop1 stop2 ...,
     где stop1 stop2 ... — список остановок автобуса bus в порядке,
     в котором они были заданы в соответствующей команде NEW_BUS.
     Если автобусы отсутствуют, выведите No buses.
*/

int main() {
    int Q, stop_count;
    string command;
    map<string, vector<string>> buses_to_stops , stops_to_buses;

    cin >> Q;

    for (int i = 0; i < Q; ++i) {
        cin >> command;

        if (command == "NEW_BUS") {
            string bus, stop;
            cin >> bus >> stop_count;
            for (int j = 0; j < stop_count; ++j) {
                cin >> stop;
                buses_to_stops[bus].push_back(stop);
                stops_to_buses[stop].push_back(bus);
            }
        } else if (command == "BUSES_FOR_STOP") {
            string stop;
            cin >> stop;
            if (stops_to_buses.count(stop) == 0) {
                cout << "No stop" << endl;
            } else {
                for (const string& bus: stops_to_buses[stop]) {
                    cout << bus << " ";
                }
                cout << endl;
            }
        } else if (command == "STOPS_FOR_BUS") {
            string bus;
            cin >> bus;
            if (buses_to_stops.count(bus) == 0) {
                cout << "No bus" << endl;
            } else {
                for (const string& stop: buses_to_stops[bus]) {
                    cout << "Stop " << stop << ": ";
                    if (stops_to_buses[stop].size() == 1) {
                        cout << "no interchange";
                    } else {
                        for (const string& stop_bus: stops_to_buses[stop]) {
                            if (stop_bus != bus) {
                                cout << stop_bus << " ";
                            }
                        }
                    }
                    cout << endl;
                }
                cout << endl;
            }
        } else if (command == "ALL_BUSES") {
            if (buses_to_stops.empty()) {
                cout << "No buses" << endl;
            } else {
                for (const auto& [bus, stops]: buses_to_stops) {
                    cout << "Bus " << bus << ": ";
                    for (const string& stop: buses_to_stops[bus]) {
                        cout << stop << " ";
                    }
                    cout << endl;
                }
                cout << endl;
            }

        }

    }
}
