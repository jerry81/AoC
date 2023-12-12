#include <fstream>
#include <string>
#include <vector>
#include <iostream>

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

vector<string> expand_galaxy(vector<string> orig, int h, int w) {
  string full_line = "";
  for (int i = 0; i < w; ++i) {
    full_line.push_back('.');
  }
  vector<string> new_galaxy;
  for (int i = 0; i < orig.size(); ++i) {
    new_galaxy.push_back(orig[i]);
    if (orig[i].find('#') == string::npos) new_galaxy.push_back(full_line);

  }

  vector<int> empty_cols;
  for (int col = 0; col < w; ++col) {
    bool found = false;
    for (int row = 0; row < h; ++row) {
      if (orig[row][col] == '#') found = true;
      if (found) break;
    }
    if (!found) empty_cols.push_back(col);
  }
  for (int c: empty_cols) {
    cout << c << " is empty " << endl;
  }
}

int main () {
  vector<string> lines = read_lines_into_vec();
  int h = lines.size();
  int w = lines[0].size();
  vector<string> expanded = expand_galaxy(lines,h,w);
  return 0;
}