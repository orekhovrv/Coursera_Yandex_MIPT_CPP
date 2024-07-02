#include <iostream>
#include <string>
#include <vector>

using namespace std;


//Определите структуру «Студент» со следующими полями: имя, фамилия, день, месяц и год рождения.
// Создайте вектор из таких структур, заполните его из входных данных и затем по запросам выведите нужные поля.
// Чтение и запись данных в этой задаче производится с использованием стандартных потоков.
//
//Формат ввода
//
//Первая строка содержит одно целое число N от 0 до 10000 — число студентов.
//
//Далее идут N строк, каждая из которых содержит две строки длиной от 1 до 15 символов — имя и фамилию очередного студента,
// и три целых числа от 0 до 1000000000 — день, месяц и год рождения.
//
//Следующая строка содержит одно целое число M от 0 до 10000 — число запросов.
//
//Следующие M строк содержат строку длиной от 1 до 15 символов — запрос,
// и целое число от 1 до 1000000000 — номер студента (нумерация начинается с 1).
//
//Формат вывода
//
//Для запроса вида name K, где K от 1 до N, выведите через пробел имя и фамилию K-го студента.
//
//Для запроса вида date K, где K от 1 до N, выведите через точку день, месяц и год рождения K-го студента.
//
//Для остальных запросов выведите bad request.
//
//NB: неверные запросы могут выходить за границы, указанные для данных.


struct Student {
public:
    string first_name, second_name;
    int birth_date, birth_month, birth_year;

    Student() {}

    Student(
            const string& first_name_,
            const string& second_name_,
            const int birth_date_,
            const int birth_month_,
            const int birth_year_
    ) {
        first_name = first_name_;
        second_name = second_name_;
        birth_date = birth_date_;
        birth_month = birth_month_;
        birth_year = birth_year_;
    }

    void PrintName() const {
        cout << first_name << " " << second_name;
    }

    void PrintBirthDate() const {
        cout << birth_date << "." << birth_month << "." <<  birth_year;
    }
};

istream& operator >>(istream& stream, Student& student) {
    stream >> student.first_name >> student.second_name >> student.birth_date >> student.birth_month >> student.birth_year;
    return stream;
}


int main() {
    int N, M, student_number;
    string query;

    cin >> N;

    vector<Student> students(N);

    for (int i = 0; i < N; ++i) {
        cin >> students[i];
    }

    cin >> M;

    for (int i = 0; i < M; ++i) {
        cin >> query >> student_number;
        if (student_number > 0 && student_number <= N) {
            if (query == "name") {
                students[student_number - 1].PrintName();
                cout << endl;
                continue;
            } else if (query == "date") {
                students[student_number - 1].PrintBirthDate();
                cout << endl;
                continue;
            }
        }
        cout << "bad request";
        cout << endl;
    }

    return 0;
}