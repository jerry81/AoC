#include <fstream>
#include <iostream>
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

int main() {
  vector<string> all_lines = read_lines_into_vec();
  vector<vector<string>> grids;
  vector<string> cur_grid;
  for (string s : all_lines) {
    if (s.find('#') == string::npos && s.find('.') == string::npos) {
      grids.push_back(cur_grid);
      cur_grid.clear();
    } else {
      cur_grid.push_back(s);
    }
  }
  grids.push_back(cur_grid);
  for (auto a : grids) {
    vector<int> nextcandidates;
    for (auto b : a) {
      // line of a grid
      int len = b.size();
      if (nextcandidates.empty()) {
        for (int i = 0; i < len - 1; ++i) {
          char c = b[i];
          char d = b[i + 1];
          if (c == d) {
            nextcandidates.push_back(i);
          }
        }
      } else {
        vector<int> nextnextcandds;
        for (int i: nextcandidates) {
          if (b[i] == b[i+1]) nextnextcandds.push_back(i);
        }
      }
      if (nextcandidates.size() == 1) cout << "split point found at " << nextcandidates[0] << endl;
    }
  }
  return 0;
}