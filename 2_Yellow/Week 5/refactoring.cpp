#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person(const string& name, const string& type) : Name(name), Type(type){}

    virtual void Walk(string& destination) const {
        cout << Type << ": " << Name << " walks to: " << destination << endl;
    };

    const string Name, Type;
};


class Student : public Person {
public:
    Student(const string& name, const string& favouriteSong)
        : Person(name, "Student"), FavouriteSong(favouriteSong) {}

    void Learn() {
        cout << Type << ": " << Name << " learns" << endl;
    }

    void Walk(string& destination) const override {
        Person::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        cout << Type <<": " << Name << " sings a song: " << FavouriteSong << endl;
    }

private:
    const string FavouriteSong;
};


class Teacher : public Person {
public:
    Teacher(const string& name, const string& subject)
        : Person(name, "Teacher"), Subject(subject) {}

    void Teach() {
        cout << Type <<": " << Name << " teaches: " << Subject << endl;
    }

private:
    const string Subject;
};


class Policeman : public Person {
public:
    Policeman(const string& name): Person(name, "Policeman") {}

    void Check(Person& p) {
        cout << Type << ": " << Name << " checks " << p.Type << ". " << p.Type << "'s name is: " << p.Name << endl;
    }
};


void VisitPlaces(const Person& person, const vector<string>& places) {
    for (auto p : places) {
        person.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
