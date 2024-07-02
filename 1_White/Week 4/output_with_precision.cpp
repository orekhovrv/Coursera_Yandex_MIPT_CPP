# include <iostream>
# include <fstream>
# include <iomanip>

using namespace std;

//В файле input.txt записаны вещественные числа, по одному на строчку.
//На стандартный вывод напечатайте эти числа в том же порядке, по одному на строке,
//но сделайте так, чтобы у каждого из них было ровно три знака после десятичной точки.


int main() {
    ifstream file_stream("input.txt");
    if (file_stream) {
        double value;
        cout << fixed << setprecision(3);
        while(file_stream  >> value) {
            cout << value << endl;
        }
    }
    return 0;
}