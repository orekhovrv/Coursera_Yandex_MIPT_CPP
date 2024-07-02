#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class User {
public:
    User(int id, int count) : user_id(id), page_count(count) {}

    int user_id;
    int page_count;

    bool operator <(const User& other) const {

//        return page_count < other.page_count;

        return (page_count < other.page_count || (!(other.page_count < page_count) && (user_id < other.user_id)));

//        if (page_count < other.page_count) {
//            return true;
//        } else if (other.page_count < page_count) {
//           return false;
//        } else {
//            return user_id < other.user_id;
//        }
    }
};


class ReadingManager {

private:
    set<User> users;

    auto Find(int user_id) const {
//        users.find();
        return find_if(
                users.begin(),
                users.end(),
                [user_id](const User& user) {return user.user_id == user_id;}
        );
    }

public:
    ReadingManager() = default;

    void Read(int user_id, int page_count) {
        auto it = Find(user_id); // N

        if (it != users.end()) {
            users.erase(it);
        }
        users.insert(User(user_id, page_count)); // logN
    }

    double Cheer(int user_id) {
        auto it = Find(user_id); // N
        if (it == users.end()) {
            return 0;
        }

        int user_count = users.size();
        if (user_count == 1) {
            return 1;
        }

        return distance(users.begin(), it) * 1.0 / (user_count - 1);
    }

};


int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    string query_type;
    int user_id;
    for (int query_id = 0; query_id < query_count; ++query_id) {
        cin >> query_type;
        cin >> user_id;
        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}