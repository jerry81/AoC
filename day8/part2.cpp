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
  vector<string> current_pos;

  while (getline(strm, l)) {
    if (l.size() < 13) continue;
    string k = l.substr(0, 3);
    if (k.find("A") != string::npos) current_pos.push_back(k);
    addresses[k] = {l.substr(7, 3), l.substr(12, 3)};
  }
  int cnt = 0;
  int zcnt = 0;
  while (zcnt < current_pos.size()) {

    for (char c : instructions) {
      zcnt = 0;
      for (int i = 0; i < current_pos.size(); ++i) {
        string cur = current_pos[i];
       // cout << "cur is " << cur << endl;
        auto [l, r] = addresses[cur];
        cur = (c == 'L') ? l : r;
        if (cur.find('Z') != string::npos) zcnt++;
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