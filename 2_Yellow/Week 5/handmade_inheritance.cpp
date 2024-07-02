//Определите до конца тела классов, соблюдая следующие требования:
//Класс Dog должен являться наследником класса Animal.
//Конструктор класса Dog должен принимать параметр типа string и инициализировать им поле Name в классе Animal.

#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
    Animal(const string& new_name) : Name(new_name) {}

    const string Name;
};


class Dog: Animal {
public:
    Dog(const string& new_name) : Animal(new_name) {}

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};