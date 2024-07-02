#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;


// Вам дана функция main, которая считывает из стандартного ввода команды по работе с набором геометрических фигур:
//Как видно из кода, есть два вида команд:
//ADD — добавить фигуру в набор;
//PRINT — для каждой фигуры в наборе распечатать название, периметр и площадь.
//Программа поддерживает три вида фигур: прямоугольник, треугольник и круг. Их добавление описывается так:
//ADD RECT width height —  добавить прямоугольник с размерами width и height (например, ADD RECT 2 3).
//ADD TRIANGLE a b c —  добавить треугольник со сторонами a, b и c (например, ADD TRIANGLE 3 4 5).
//ADD CIRCLE r —  добавить круг радиуса r (например, ADD CIRCLE 5).

// Не меняя функцию main, реализуйте недостающие функции и классы:
//базовый класс Figure с чисто виртуальными методами Name, Perimeter и Area;
//классы Triangle, Rect и Circle, которые являются наследниками класса Figure и переопределяют его виртуальные методы;
//функцию CreateFigure, которая в зависимости от содержимого входного потока создаёт shared_ptr<Rect>, shared_ptr<Triangle> или shared_ptr<Circle>.
//Гарантируется, что размеры всех фигур — это натуральные числа не больше 1000. В качестве значения PI используйте 3,14.

double pi = 3.14;


class Figure {
public:
    virtual string Name() const = 0;

    virtual double Perimeter() const = 0;

    virtual double Area() const = 0;
protected:
    void Initialize() {
        InitializePerimeter();
        InitializeArea();
    }

    virtual void InitializePerimeter() = 0;

    virtual void InitializeArea() = 0;

    double perimeter;
    double area;
    string name;
};


class Triangle: public Figure {
public:
    Triangle(int a_, int b_, int c_) {
        a = a_;
        b = b_;
        c = c_;
        Initialize();
    }

    string Name() const override {
        return name;
    }

    double Perimeter() const override {
        return perimeter;
    }

    double Area() const override {
        return area;
    }
private:
    const string name = "TRIANGLE";
    int a, b, c;

    void InitializePerimeter() override {
        perimeter = a + b + c;
    }

    void InitializeArea() override {
        double s = double(a + b + c) / 2;
        area = sqrt(s * (s - a) * (s - b) * (s - c));
    }
};


class Rect: public Figure {
public:
    Rect(int a_, int b_) {
        a = a_;
        b = b_;
        Initialize();
    }

    string Name() const override {
        return name;
    }

    double Perimeter() const override {
        return perimeter;
    }

    double Area() const override {
        return area;
    }

private:
    const string name = "RECT";
    int a, b;

    void InitializePerimeter() override {
        perimeter = 2 * (a + b);
    }

    void InitializeArea() override {
        area = a * b;
    }
};


class Circle: public Figure {
public:
    Circle(int r_) {
        r = r_;
        Initialize();
    }

    string Name() const override {
        return name;
    }

    double Perimeter() const override {
        return perimeter;
    }

    double Area() const override {
        return area;
    }

private:
    const string name = "CIRCLE";
    int r;

    void InitializePerimeter() override {
        perimeter = 2 * pi * r;
    }

    void InitializeArea() override {
        area = pi * r * r;
    }
};


shared_ptr<Figure> CreateFigure(istream& stream) {
    string figure_type;
    stream >> figure_type;
    if (figure_type == "RECT") {
        int a, b;
        stream >> a >> b;
        return make_shared<Rect>(a, b);
    } else if (figure_type == "TRIANGLE") {
        int a, b, c;
        stream >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    } else if (figure_type == "CIRCLE") {
        int r;
        stream >> r;
        return make_shared<Circle>(r);
    } else {
        throw runtime_error("");
    }
}


int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> ws;
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}