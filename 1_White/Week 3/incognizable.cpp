/*
Определите тип Incognizable, для которого следующий код будет корректен:
*/

struct Incognizable {
    int value_1 = 0;
    int value_2 = 0;
};

int main() {
    Incognizable a;
    Incognizable b = {};
    Incognizable c = {0};
    Incognizable d = {0, 1};
    return 0;
}