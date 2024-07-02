# include <iostream>
# include <fstream>

using namespace std;


//Ваша программа должна считать содержимое файла input.txt и напечатать его на экран без изменений.
//Гарантируется, что содержимое файла input.txt заканчивается переводом строки.


int main() {
    ifstream file_input_stream("1_White\\Week 4\\input.txt");
    if (file_input_stream) {
        string value;
        while(getline(file_input_stream,  value)) {
            cout << value << endl;
        }
    }
    return 0;
}