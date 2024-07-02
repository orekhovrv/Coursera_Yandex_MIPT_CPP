#include <string>
#include <map>
#include <algorithm>

using namespace std;

/*
 Реализуйте класс ReversibleString, хранящий строку и поддерживающий методы 
 Reverse для переворота строки и ToString для получения строки.  
 */

class ReversibleString {
public:
    ReversibleString() {}

    explicit ReversibleString(const string& new_value) {
        value = new_value;
    }

    void Reverse() {
        reverse(begin(value), end(value));
    }

    string ToString() const {
        return value;
    }
    
private:
    string value;

};


//int main() {
//    ReversibleString s("live");
//    s.Reverse();
//    cout << s.ToString() << endl;
//
//    s.Reverse();
//    const ReversibleString& s_ref = s;
//    string tmp = s_ref.ToString();
//    cout << tmp << endl;
//
//    ReversibleString empty;
//    cout << '"' << empty.ToString() << '"' << endl;
//
//    return 0;
//}