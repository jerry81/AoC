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

int main() {
}