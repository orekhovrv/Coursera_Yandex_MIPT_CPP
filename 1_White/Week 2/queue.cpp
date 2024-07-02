#include <vector>
#include <iostream>

using namespace std;


/* Люди стоят в очереди, но никогда не уходят из её начала, зато могут приходить в конец  и уходить оттуда.
 * Более того, иногда некоторые люди могут прекращать и начинать беспокоиться из-за того,
 * что очередь не продвигается.
Будем считать, что люди в очереди нумеруются целыми числами, начиная с 0.

 Реализуйте обработку следующих операций над очередью:
WORRY i: пометить i-го человека с начала очереди как беспокоящегося;
QUIET i: пометить i-го человека как успокоившегося;
COME k: добавить k спокойных человек в конец очереди;
COME -k: убрать k человек из конца очереди;
WORRY_COUNT: узнать количество беспокоящихся людей в очереди.

Изначально очередь пуста.

Формат ввода
Количество операций Q, затем описания операций.
Для каждой операции WORRY i и QUIET i гарантируется, что
 человек с номером i существует в очереди на момент операции.
Для каждой операции COME -k гарантируется, что k не больше текущего размера очереди.

Формат вывода
Для каждой операции WORRY_COUNT выведите одно целое число — количество беспокоящихся людей в очереди. */


int main() {
    int Q, parameter;
    string operation;
    vector<int> worrying_people;
    int queue_size = 0;

    cin >> Q;
    for (int i = 0; i < Q; i++) {
        cin >> operation;
        if (operation == "WORRY_COUNT") {
            cout << worrying_people.size();
        } else {
            cin >> parameter;

            if (operation == "WORRY") {
                worrying_people.push_back(parameter);
            } else if (operation == "QUIET") {
                vector<int> new_worrying_people;
                for (int worrying_person: worrying_people) {
                    if (worrying_person != parameter) {
                        new_worrying_people.push_back(worrying_person);
                    }
                }
                worrying_people = new_worrying_people;
            } else if (operation == "COME") {
                int last_removed = queue_size + parameter;
                if (parameter < 0) {
                    vector<int> new_worrying_people;
                    for (int worrying_person: worrying_people) {
                        if (worrying_person < last_removed) {
                            new_worrying_people.push_back(worrying_person + parameter);
                        }
                    }
                    worrying_people = new_worrying_people;
                }
                queue_size = last_removed;
            }
        }
    }

    return 0;
}


