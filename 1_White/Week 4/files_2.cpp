# include <iostream>
# include <fstream>
# include <iomanip>

using namespace std;


//Снова считайте все содержимое файла input.txt, но на этот раз выведите его в файл output.txt .
//Точно так же гарантируется, что содержимое файла input.txt заканчивается переводом строки.


int main() {
    ifstream file_input_stream("1_White\\Week 4\\input.txt");
    ofstream file_output_stream("output.txt");

    if (file_input_stream) {
        string value;
        while(getline(file_input_stream,  value)) {
            file_output_stream << value << endl;
        }
    }
    return 0;
}