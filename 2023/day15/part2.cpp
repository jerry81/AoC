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
      cout << "eq situation " << endl;
      cout << "assinging " << stoi(v) <<  " into position " << h << "," << k << endl;
    }
  }
  vector<vector<tuple<string, int>>> slots(256);
  cout << sum << endl;
  return 0;
}