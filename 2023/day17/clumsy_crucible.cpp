#include <fstream>
#include <iostream>
#include <set>
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

// DIR: 0L 1U 2R 3D
int dfs(int y, int x, int dir, int consecutive, set<pair<int, int>> visited,
        vector<string> &grid, int &h, int &w) {
  visited.insert({y, x});
  if (y == h - 1 && x == w - 1) return grid[y][x];

  // three choices: continue, left, right
  vector<int> nxt_dirs;
  switch (dir) {
    case 0: {
      if (consecutive < 2) nxt_dirs.push_back(0);

      nxt_dirs.push_back(1);
      nxt_dirs.push_back(3);
      break;
    }
    case 1: {
      if (consecutive < 2) nxt_dirs.push_back(1);

      nxt_dirs.push_back(0);
      nxt_dirs.push_back(2);
      break;
    }
    case 2: {
      if (consecutive < 2) nxt_dirs.push_back(2);

      nxt_dirs.push_back(1);
      nxt_dirs.push_back(3);
      break;
    }
    default: {
      if (consecutive < 2) nxt_dirs.push_back(3);

      nxt_dirs.push_back(0);
      nxt_dirs.push_back(2);
    }
  }
}

int main() {
  vector<string> grid = read_lines_into_vec();
  int h = grid.size();
  int w = grid[0].size();
  cout << "grid" << endl;
  for (string s : grid) cout << s << endl;
  // dfs?
  return 0;
}