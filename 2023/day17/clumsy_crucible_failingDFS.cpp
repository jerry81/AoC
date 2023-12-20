#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

const string FNAME = "vsm.txt";

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
long long int dfs(int y, int x, int dir, int consecutive,
                  set<pair<int, int>> visited, vector<string> &grid, int &h,
                  int &w) {
  // cout << "visiting " << y << ","<<x << endl;
  long long int cur_val = grid[y][x] - '0';
  cout << "cur_val is " << cur_val << endl;
  cout << "y is " << y << " and x is " << x << endl;
  // visited.insert({y, x});
  if (y == h - 1 && x == w - 1) return cur_val;

  // if (y == 12) cout << "y " << y << " and x " << x << endl;

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

  long long int res = INT_MAX;
  for (int nd : nxt_dirs) {
    set<pair<int, int>> nvisited = visited;
    int ny = y;
    int nx = x;
    switch (nd) {
      case 0: {
        nx--;
        break;
      }
      case 1: {
        ny--;
        break;
      }
      case 2: {
        nx++;
        break;
      }
      default: {
        ny++;
      }
    }
    if (ny < 0 || nx < 0) continue;

    if (ny >= h || nx >= w) continue;

    if (nvisited.find({ny, nx}) != nvisited.end()) continue;

    nvisited.insert({ny, nx});

    int cons = (nd == dir) ? consecutive + 1 : 1;
    res = min(res, dfs(ny, nx, nd, cons, nvisited, grid, h, w));
  }
  cout << "curv" << cur_val << endl;
  cout << "res " << res << endl;
  long long int sm = cur_val + res;
  return sm;
}

int main() {
  vector<string> grid = read_lines_into_vec();
  int h = grid.size();
  int w = grid[0].size();
  set<pair<int, int>> visited;
  cout << "h " << h << " and w " << w << endl;
  set<pair<int, int>> visited2;
  long long int res = INT_MAX;
  res = min(res, dfs(0, 1, 2, 1, visited, grid, h, w));
  res = min(res, dfs(1, 0, 3, 1, visited2, grid, h, w));
  cout << "res is " << res << endl;
  // dfs?
  return 0;
}