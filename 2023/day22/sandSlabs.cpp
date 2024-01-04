#include <fstream>
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
  vector<pair<tuple<int, int, int>, tuple<int, int, int>>> slabs_processed;

  vector<string> slabs = read_lines_into_vec();
  for (string s : slabs) {
    vector<string> tokens = split_by(s, '~');
    vector<string> tk1 = split_by(tokens[0], ',');
    vector<string> tk2 = split_by(tokens[1], ',');
    slabs_processed.push_back({{stoi(tk1[0]), stoi(tk1[1]), stoi(tk1[2])},
                               {stoi(tk2[0]), stoi(tk2[1]), stoi(tk2[2])}});
  }
}