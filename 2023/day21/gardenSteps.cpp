#include <fstream>
#include <iostream>
#include <queue>
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

int main() {
  const vector<pair<int, int>> DIRECTIONS = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  vector<string> grid = read_lines_into_vec();
  pair<int, int> start;
  int h = grid.size();
  int w = grid[0].size();
  bool found = false;
  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      if (grid[y][x] == 'S') {
        start = {y, x};
        found = true;
        break;
      }
    }
    if (found) break;
  }
  queue<pair<int, int>> q;
  q.push(start);

  while (!q.empty()) {
    queue<pair<int, int>> nq;
    set<pair<int, int>> visited;
    while (!q.empty()) {
      auto [y, x] = q.front();
      q.pop();
      if (visited.find({y, x}) != visited.end()) continue;

      visited.insert({y, x});
      for (auto [dy, dx] : DIRECTIONS) {
        int ny = dy + y;
        int nx = dx + x;

        if (ny >= h || nx >= w || ny < 0 || nx < 0) continue;
      }
    }
  }
}