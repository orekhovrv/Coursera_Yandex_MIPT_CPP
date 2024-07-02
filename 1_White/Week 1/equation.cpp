#include <iostream>
#include <cmath>

using namespace std;


/* На вход вашей программы в стандартном потоке ввода подаются действительные коэффициенты A, B и C  уравнения Ax² + Bx + C = 0.
 * Выведите все его различные действительные корни в поток вывода в любом порядке, при этом разделяя корни пробелами.
 * Гарантируется, что хотя бы один из коэффициентов уравнения не равен нулю.*/


int main() {
    double a;
    double b;
    double c;

    cin >> a >> b >> c;

    if (a == 0) {
        if (b != 0) {
            cout << -c / b;
        }
    } else {
        double discriminant = pow(b, 2) - 4 * a * c;
        if (discriminant >= 0) {
            double x_1 =  (- b + pow(discriminant, 0.5)) / (2 * a);
            cout << x_1;
            if (discriminant != 0) {
                double x_2 = (- b - pow(discriminant, 0.5)) / (2 * a);
                cout << " " << x_2;
            }
        }
    }



    return 0;
}
