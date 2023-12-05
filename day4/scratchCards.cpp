#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
  std::ifstream inputFile("input.txt");  // Replace "your_input_file.txt" with
                                           // the actual file name
  string line;
  long long int res = 0;
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
    if (match > 0) {
      res+=pow(2,match-1);
    }
  }
  cout << res << endl;
  return 0;
}