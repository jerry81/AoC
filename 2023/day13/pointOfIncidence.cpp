#include <fstream>
#include <iostream>
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

bool checkline(string s, int start) {
  int sz = s.size();
  int offset = 0;
  while ((offset + start + 1) < sz && (start - offset) >= 0) {
    // if (start == 2) {
    //   cout << "comparing " << start - offset << " to " << start + 1 + offset
    //        << endl;
    //   cout << "comparingv " << s[start - offset] << " to "
    //        << s[start + 1 + offset] << endl;
    // }
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
    // cout << "cands is now " << endl;
    // for (auto a : cands) cout << a << endl;
    // line of a grid
    vector<int> nxt;
    if (cands.empty()) {
      for (int i = 0; i < sz - 1; ++i) {
        if (checkline(b, i)) nxt.push_back(i);
      }
    } else {
      for (int i : cands) {
        if (checkline(b, i)) nxt.push_back(i);
      }
    }
    if (nxt.empty()) return -10;
    cands = nxt;
  }

  if (cands.size() == 1) return cands[0];
  return -10;
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
  // cout << "flipped " << endl;
  // for (string s : newLines) {
  //   cout << s << endl;
  // }
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
  long long int res = 0;
  for (auto a : grids) {
    long long int sum = 0;
    int hres = horizontalCheck(a) + 1;  // hres to left

    cout << "hres is " << hres << endl;

    int vres = verticalCheck(a) + 1;

    cout << "vres is " << vres << endl;
    if (hres > 0) {
      sum += hres;
    }
    if (vres > 0) {
      sum += vres * 100;
    }

    // if (vres >= 0) sum+= vres;
    cout << "sum is " << sum << endl;
    res += sum;
  }
  cout << "res is " << res << endl;
  return 0;
}