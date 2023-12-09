#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>

using namespace std;

const string FNAME = "input.txt";

int main() {
  ifstream strm(FNAME);
  string instructions;
  getline(strm, instructions);
  unordered_map<string, pair<string, string>> addresses;
  string l;
  vector<string> current_pos;

  // find index 0(instruction) coming back to start.

  while (getline(strm, l)) {
    if (l.size() < 13) continue;
    string k = l.substr(0, 3);
    if (k.find("A") != string::npos) current_pos.push_back(k);
    addresses[k] = {l.substr(7, 3), l.substr(12, 3)};
  }
  string start1 = current_pos[0];
  unordered_set<string> references;
  long long int cnt = 0;
  int zcnt = 0;
  while (zcnt < current_pos.size()) {

    for (int j = 0; j < instructions.size(); ++j) {
      char c = instructions[j];
      zcnt = 0;
      for (int i = 0; i < current_pos.size(); ++i) {

        string cur = current_pos[i];
        if (cnt > 50000) return 0;
        if (j == 0) {
          if (i == 0) {
            if (references.find(cur) != references.end()) {
              cout << "dejavu bb" << endl;
              cout << "cur is " << cur << endl;
            } else {
              references.insert(cur);
            }

          }
        }
       // cout << "cur is " << cur << endl;
        auto [l, r] = addresses[cur];
        cur = (c == 'L') ? l : r;
        if (cur.find('Z') != string::npos) {
          zcnt++;
        }
        current_pos[i] = cur;
      //  cout << "zcnt is " << zcnt << endl;
        if (zcnt >= current_pos.size()) {
          cout << "found to be " << cnt << endl;
          return 0;
        }
      }
      cnt++;
    }
  }

  cout << "cnt " << cnt << endl;
}

/*

item 0 always loops to ending 0 and no other enders!

after experimentation:
THe start nodes (contain A) are never ref'd by other nodes
- cycles are not huge, can easily be calculated

*/