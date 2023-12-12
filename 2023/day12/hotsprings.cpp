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


vector<string> split_by_space(string s) {
  vector<string> newTokens;
  istringstream spaceStream(s);
  string spaceToken;
  while (spaceStream >> spaceToken) {
    newTokens.push_back(spaceToken);
  }
  return newTokens;
}

int main() {
  vector<string> lines = read_lines_into_vec();
  for (string l: lines) {
    vector<string> splBySpace = split_by_space(l);
    string layout = splBySpace[0];
    string grouping = splBySpace[1];
    cout << "grouping is " << grouping << endl;
  }
  // split lines
  return 0;
}