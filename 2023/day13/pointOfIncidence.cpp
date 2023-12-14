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

bool checkline(string s, int start) {
  int sz = s.size();
  int offset = 0;
  while ((offset + start + 1) < sz && (start - offset) >= 0) {
    if (s[start - offset] != s[start + 1 + offset]) return false;

    offset++;
  }
  return true;
}

int horizontalCheck(vector<string> lines) {
  // check all checkable items
  int sz = lines[0].size();
  vector<int> cands;
  for (auto b : lines) {
    // line of a grid
    vector<int> nxt;
    if (cands.empty()) {
      for (int i = 0; i < sz-1; ++i) {
        if (checkline(b, i)) nxt.push_back(i);
      }
    } else {
      for (int i: cands) {
        if (checkline(b,i)) nxt.push_back(i);
      }
    }
    cands = nxt;
  }

  if (cands.size() == 1) return cands[0];
  return -1;
}

int verticalCheck(vector<string> lines) {
  // convert vertical lines to horizontal lines
  int w = lines[0].size();
  int h = lines.size();
  vector<string> newLines(w, "");
  for (int c = 0; c < w; ++c) {
    for (int r = 0; r < h; ++r) {
        newLines[c].push_back(lines[r][c]);
    }
  }
  return horizontalCheck(newLines);
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
  long long int res;
  for (auto a : grids) {
    long long int sum = 0;
    int hres = horizontalCheck(a) + 1;  // hres to left

    cout << "hres is " << hres << endl;

    int vres = verticalCheck(a) + 1;
    if (hres > 0) {
      sum += hres;
    } else {
      sum += vres * 100;
    }

    // if (vres >= 0) sum+= vres;
    cout << "sum is " << sum << endl;
    res += sum;
  }
  cout << "res is " << res << endl;
  return 0;
}