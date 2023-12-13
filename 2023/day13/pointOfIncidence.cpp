#include <fstream>
#include <string>
#include <vector>
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

int main() {
  vector<string> all_lines = read_lines_into_vec();
  vector<vector<string>> grids;
  vector<string> cur_grid;
  for (string s: all_lines) {
    if (s.find('#') == string::npos && s.find('.') == string::npos) {
      grids.push_back(cur_grid);
      cur_grid.clear();
    } else {
      cur_grid.push_back(s);
    }
  }
  grids.push_back(cur_grid);
  for (auto a: grids) {
    cout << "printing grid " << endl;
    for (auto b:a) {
      cout << b << endl;
    }
  }
  return 0;
}