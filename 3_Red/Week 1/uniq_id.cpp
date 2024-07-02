#include <string>
#include <vector>
using namespace std;


// Реализуйте этот макрос так, чтобы функция main компилировалась

#define GLUE_HELPER(x, y) x##y
#define GLUE(x, y) GLUE_HELPER(x, y)

#define UNIQ_ID GLUE(x, __LINE__)



int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}