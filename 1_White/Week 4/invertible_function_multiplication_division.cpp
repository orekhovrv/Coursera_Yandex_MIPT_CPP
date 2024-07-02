# include <vector>
# include <algorithm>
# include <iostream>
# include <map>

using namespace std;


/*
 Добавьте в класс Function из задачи «Обратимая функция» обработку умножения ('*') и деления ('/').
 Гарантируется отсутствие элементарных операций умножения и деления на 0.
 */


class FunctionPart {
public:
    FunctionPart(char new_operation, double new_value) {
        operation = new_operation;
        value = new_value;
    }

    double Apply(double source_value) const {
        if (operation == '+') {
            return source_value + value;
        } else if (operation == '-') {
            return source_value - value;
        } else if (operation == '*') {
            return source_value * value;
        } else {
            return source_value / value;
        }
    }

    void Invert() {
        operation = inverted_operations[operation];
    }

private:
    char operation;
    double value;
    map<char, char> inverted_operations = {
            {'+', '-'},
            {'-', '+'},
            {'*', '/'},
            {'/', '*'}
    };
};


class Function {
public:
    void AddPart(char new_operation, double new_value) {
        parts.push_back(FunctionPart(new_operation, new_value));
    }

    void Invert() {
        for (auto& part: parts) {
            part.Invert();
        }
        reverse(begin(parts), end(parts));
    }

    double Apply(double value) const {
        for (auto& part: parts) {
            value = part.Apply(value);
        }
        return value;
    }

private:
    vector<FunctionPart> parts;
};


//struct Image {
//    double quality;
//    double freshness;
//    double rating;
//};
//
//struct Params {
//    double a;
//    double b;
//    double c;
//};
//
//Function MakeWeightFunction(const Params& params,
//                            const Image& image) {
//    Function function;
//    function.AddPart('*', params.a);
//    function.AddPart('-', image.freshness * params.b);
//    function.AddPart('+', image.rating * params.c);
//    return function;
//}
//
//double ComputeImageWeight(const Params& params, const Image& image) {
//    Function function = MakeWeightFunction(params, image);
//    return function.Apply(image.quality);
//}
//
//double ComputeQualityByWeight(const Params& params,
//                              const Image& image,
//                              double weight) {
//    Function function = MakeWeightFunction(params, image);
//    function.Invert();
//    return function.Apply(weight);
//}
//
//int main() {
//    Image image = {10, 2, 6};
//    Params params = {4, 2, 6};
//    cout << ComputeImageWeight(params, image) << endl;
//    cout << ComputeQualityByWeight(params, image, 52) << endl;
//    return 0;
//}
