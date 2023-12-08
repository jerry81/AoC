#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const string FNAME = "input.txt";

int main() {
  ifstream strm(FNAME);
  string instructions;
  getline(strm, instructions);
  unordered_map<string, pair<string, string>> addresses;
  string l;

  while (getline(strm, l)) {
    if (l.size() < 13) continue;
    addresses[l.substr(0, 3)] = {l.substr(7, 3), l.substr(12, 3)};
  }
  int cnt = 0;
  string cur = "AAA";
  while (cur != "ZZZ") {
    for (char c : instructions) {
      auto [l, r] = addresses[cur];
      cur = (c == 'L') ? l : r;
      cnt++;
    }
  }
  cout << "cnt " << cnt << endl;
}