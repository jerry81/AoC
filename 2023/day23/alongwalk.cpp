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

/*
direction
0 free
1 d
2 r
*/
long long int dfsbt(vector<string> &grid, int &h, int &w, int y, int x,
                    int direction, set<pair<int, int>> visited) {
  visited.insert({y, x});
  if (y < 0 || x < 0 || y >= h || x >= w) return -1;
  int cursq = grid[y][x];
  switch (cursq) {
    case '.': {
      // can we choose direction
    }
    case '#': {
      return -1;
    }
    case '>': {
      if (visited.find({y, x + 1}) != visited.end()) return -1;

      if (direction == 1) return -1;

      return 1 + dfsbt(grid, h, w, y, x + 1, 2, visited);
    }
    case 'v': {
      if (visited.find({y+1, x}) != visited.end()) return -1;

      if (direction == 2) return -1;

      return 1 + dfsbt(grid, h, w, y+1, x, 1, visited);
    }
    default: {
      cout << "unhandled case for " << cursq << endl;
    }
  }
}

int main() {
  vector<string> grid = read_lines_into_vec();
  int h = grid.size();
  int w = grid[0].size();
  int startx = grid[0].find('.');
  set<pair<int, int>> visited;
  cout << dfsbt(grid, h, w, 0, startx, 0, visited);

  return 0;
}
