#include <fstream>
#include <iostream>
#include <map>
#include <queue>
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

struct TupleComparator {
  bool operator()(const tuple<int, int, int, int, int>& a,
                  const tuple<int, int, int, int, int>& b) const {
    return get<0>(a) > get<0>(b);  // TIL tuple unwrap
  }
};

int main() {
  const vector<int> BACKWARDS = {2, 3, 0, 1};
  const vector<pair<int, int>> DIRECTIONS = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
  vector<string> grid = read_lines_into_vec();
  int h = grid.size();
  int w = grid[0].size();

  // DIR 0L1U2R3D
  priority_queue<tuple<int, int, int, int, int>,
                 vector<tuple<int, int, int, int, int>>, TupleComparator>
      q;  // use the generics
          // the "type", the container impl, the custom comparator
  q.push({0, 0, 0, -1, 0});
  map<tuple<int, int, int, int>, int> visited;

  while (!q.empty()) {
    auto [d, y, x, dir, cons] = q.top();
    tuple<int, int, int, int> hsh = {y, x, dir, cons};
    q.pop();
    if (visited.find(hsh) != visited.end()) continue;

    visited[hsh] = d;
    if (cons >= 0 && cons < 4) {  // continue
      auto [dy, dx] = DIRECTIONS[dir];

      int ny = dy + y;
      int nx = dx + x;
      if (ny < 0 || nx < 0) continue;

      if (ny >= h || nx >= w) continue;
      int new_cost = (grid[ny][nx] - '0') + d;

      int new_cons = cons + 1;

      q.push({new_cost, ny, nx, dir, new_cons});
    } else if (cons > 10) {  // must turn
      continue;
    } else {  // can turn
      for (int i = 0; i < 4; ++i) {
        auto [dy, dx] = DIRECTIONS[i];
        if (dir == BACKWARDS[i]) continue;

        int ny = dy + y;
        int nx = dx + x;

        if (ny < 0 || nx < 0) continue;

        if (ny >= h || nx >= w) continue;

        int new_cost = (grid[ny][nx] - '0') + d;

        int new_cons = dir == i ? cons + 1 : 1;

        q.push({new_cost, ny, nx, i, new_cons});
      }
    }
  }
  int res = 1e9;
  for (auto [k, v] : visited) {
    auto [y, x, _, __] = k;
    if (y == h - 1 && x == w - 1) res = min(res, v);
  }
  cout << "res is " << res << endl;
  // dfs?
  return 0;
}