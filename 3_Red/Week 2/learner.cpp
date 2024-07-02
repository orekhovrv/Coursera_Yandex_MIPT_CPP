#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <set>

using namespace std;

class Learner {
 private:
//  vector<string> dict;
  set<string> dict;
  size_t words_number = 0;

 public:
    int Learn(const vector<string>& words) {
        for (const auto& word : words) {
            dict.insert(word);
        }
        int newWords = dict.size() - words_number;
        words_number = dict.size();
        return newWords;
    }

  vector<string> KnownWords() {
    return vector(dict.begin(), dict.end());
  }
};

int main() {
    Learner learner;
    string line;
    while (getline(cin, line)) {
        vector<string> words;
        stringstream ss(line);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        cout << learner.Learn(words) << "\n";
    }
    cout << "=== known words ===\n";
    for (auto word : learner.KnownWords()) {
        cout << word << "\n";
    }
}
