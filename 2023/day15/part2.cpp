#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string FNAME = "input.txt";

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

int main() {
  string s = read_lines_into_vec()[0];
  vector<string> tks = split_by(s,',');
  int sum = 0;
  for (auto tk: tks) {
    int cur = 0;
    for (char c: tk) {
      cur = hsh(c, cur);
    }
    sum+=cur;
  }
  cout << sum << endl;
  return 0;
}