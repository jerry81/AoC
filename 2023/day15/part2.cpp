#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string FNAME = "sm.txt";

vector<string> read_lines_into_vec() {
  ifstream strm(FNAME);
  string line;
  vector<string> lines;
  while (getline(strm, line)) {
    lines.push_back(line);
  }
  return lines;
}

vector<string> split_by(string s, char c) {
  vector<string> newTokens;
  istringstream strm(s);
  string tk;
  while (getline(strm, tk, c)) {
    newTokens.push_back(tk);
  }
  return newTokens;
}

int hsh(char c, int init) {
  init+=c;
  init *= 17;
  return init % 256;
}

int hsh_s(string s) {
  int cur = 0;
  for (char c: s) {
    cur = hsh(c,cur);
  }
  return cur;
}

int main() {
  string s = read_lines_into_vec()[0];
  vector<string> tks = split_by(s,',');
  int sum = 0;
  vector<vector<tuple<string, int>>> slots(256);

  for (auto tk: tks) {
    string k;
    string v;
    if (tk.find('-') != string::npos) {
      k = split_by(tk, '-')[0];
      int h = hsh_s(k);
      cout << "removing " << k << " from position " << h << endl;
    } else {
      auto ve = split_by(tk, '=');
      k = ve[0];
      v = ve[1];
      int h = hsh_s(k);
      int vi = stoi(v);
      auto cur_slot = slots[h];
      auto new_t = make_tuple(k, vi);

      bool found = false;
      for (int idx = 0; idx < cur_slot.size(); ++idx) {
        auto [ks, _] = cur_slot[idx];
        if (ks == k) {
          cur_slot[idx] = new_t;
          found = true;
          break;
        }
      }
      if (found) {
        slots[h] = cur_slot;
      } else {
        slots[h].push_back(new_t);
      }
    }
  }
  for (int i = 0; i < slots.size(); ++i) {
    cout << "slot " << i << endl;
    auto v = slots[i];
    for (auto [k,v2]: v) {
      cout << k << ":"<<v2 << endl;
    }
  }
  cout << sum << endl;
  return 0;
}