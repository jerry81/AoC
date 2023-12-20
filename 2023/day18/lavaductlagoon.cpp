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
  vector<string> lines = read_lines_into_vec();
  pair<int,int> pt = {0,0};
  pair<int,int> maxes = {0,0};
  vector<vector<string>> instructions;
  for (auto line : lines) {
    vector<string> tokens = split_by(line, ' ');
    string d = tokens[0];
    int mag = stoi(tokens[1]);
    int dy = 0;
    int dx = 0;
    if (d == "U") {
      dy = -1*mag;
    } else if (d == "R") {
      dx = mag;
    } else if (d == "D") {
      dy = mag;
    } else {
      dx = -1*mag;
    }
    instructions.push_back(tokens);
  }

  return 0;
}
// get bounds of the
// first milestone:  print out the input map