#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
  std::ifstream inputFile("input.txt");  // Replace "your_input_file.txt" with
  vector<int> multipliers(214, 1);                   // the actual file name
  string line;
  long long int res = 0;
  int idx = 0;
  while (std::getline(inputFile, line)) {
    auto breaker = line.find('|');
    string a = line.substr(0, breaker);
    string b = line.substr(breaker + 1);
    unordered_set<string> have;
    istringstream spaceStream(a);
    string spaceToken;
    while (spaceStream >> spaceToken) {
      have.insert(spaceToken);
    }
    istringstream spaceStreamB(b);
    int match = 0;
    while (spaceStreamB >> spaceToken) {
      if (have.find(spaceToken) != have.end()) match++;
    }
    int c_mult = multipliers[idx];
    if (match > 0) {
      for (int i = 1; i <= match; ++i) {
        int cur = idx+i;
        if (cur < 214) {
          multipliers[cur]+=c_mult;
        }
      }
    }
    ++idx;
  }
  for (int i: multipliers) {
    res+=i;
  }
  cout << "res is " << res << endl;
  return 0;
}