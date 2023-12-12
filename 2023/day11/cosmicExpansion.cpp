#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const string FNAME = "input.txt";

string to_h(int y, int x) { return to_string(y) + "," + to_string(x); }

pair<int, int> to_pos(string s) {
  auto pos = s.find(',');
  return {stoi(s.substr(0, pos)), stoi(s.substr(pos + 1))};
}

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
  vector<string> returned;
  for (int r = 0; r < new_galaxy.size(); ++r) {
    string ngalaxyr = "";
    string row = new_galaxy[r];
    for (int c = 0; c < row.size(); ++c) {
      ngalaxyr += row[c];
      if (find(empty_cols.begin(), empty_cols.end(), c) != empty_cols.end()) ngalaxyr += '.';
    }
    returned.push_back(ngalaxyr);
  }
  return returned;
}

int main() {
  vector<string> lines = read_lines_into_vec();
  int h = lines.size();
  int w = lines[0].size();
  vector<string> expanded = expand_galaxy(lines, h, w);

  vector<pair<int, int>> items;
  for (int r = 0; r < expanded.size(); ++r) {
    string row = expanded[r];
    // cout << row << endl;
    for (int c = 0; c < row.size(); ++c) {
      if (row[c] == '#') {
        items.push_back({r, c});
      }
    }
  }
  int totalDists = 0;
  int count = 0;

  for (int i = 0; i < items.size() - 1; ++i) {
    // 12, 13 14 15 16 17..
    // 23 24 25 26
    // 34 35 36 37...
    // ..
    // 78
    pair<int, int> point1 = items[i];
    auto [y1, x1] = point1;
    for (int j = i + 1; j < items.size(); ++j) {
      // cout << i << " to " << j << endl;

      pair<int, int> point2 = items[j];
      auto [y2, x2] = point2;
      // cout << y1 << "," << x1 << endl;
      // cout << " to " << endl;
      // cout << y2 << "," << x2 << endl;
      count++;
      int dist = abs(y2 - y1) + abs(x2 - x1);
      // cout << "dist is " << dist << endl;
      totalDists += dist;
    }
  }
  cout << "count is " << count << endl;
  cout << "totalDist is " << totalDists << endl;
  return 0;
}