#include "test_runner.h"

#include <ostream>
using namespace std;

//#define PRINT_VALUES(out, x, y) \
    out << (x) << endl << (y) << endl


#define PRINT_VALUES(out, x, y) { \
    out << (x) << endl; out << (y) << endl; \
} \

int main() {
    TestRunner tr;
    tr.RunTest(
        [] {
            ostringstream output;
            PRINT_VALUES(output, 5, "red belt");
            ASSERT_EQUAL(output.str(), "5\nred belt\n");
        },
        "PRINT_VALUES usage example"
    );

    ostringstream output;
    if (true) {
        PRINT_VALUES(output, 5, "red belt");
    }
    ASSERT_EQUAL(output.str(), "5\nred belt\n");

    output.str("");
    output.clear();
    if (false) {
    } else {
        PRINT_VALUES(output, 5, "red belt");
    }
    ASSERT_EQUAL(output.str(), "5\nred belt\n");

    output.str("");
    output.clear();
    for (int i = 0; i < 3; i++) {
        PRINT_VALUES(output, 5, "red belt");
    }
    ASSERT_EQUAL(output.str(), "5\nred belt\n5\nred belt\n5\nred belt\n");

    return 0;
}
