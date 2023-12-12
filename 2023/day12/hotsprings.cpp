#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

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

int main() {
  vector<string> lines = read_lines_into_vec();
  for (string l: lines) {
    vector<string> splBySpace = split_by(l, ' ');
    string layout = splBySpace[0];
    string grouping = splBySpace[1];
    vector<string> splByComma = split_by(grouping, ',');
  }
  // split lines
  return 0;
}