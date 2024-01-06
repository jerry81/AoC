#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <map>

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

const vector<pair<int, int>> DIRECTIONS = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

long long int LOW_NUM = -9999999999;

map<pair<int,int>, long long int> memo; // y,x

long long int dfsbt(vector<string> &grid, int &h, int &w, int y, int x, set<pair<int, int>> visited) {
  visited.insert({y, x});
  if (y < 0 || x < 0 || y >= h || x >= w) return LOW_NUM;

  int cursq = grid[y][x];

  if (cursq == '#') return LOW_NUM;

  switch (cursq) {
    case '.': {
      if (y == h - 1) {
        return 0;
      }
      // can we choose direction
      // return max of the 4 directions
      long long int mx = -1;
      for (auto [dy, dx] : DIRECTIONS) {
        if (visited.find({y + dy, x + dx}) != visited.end()) continue;

        mx = max(mx, 1 + dfsbt(grid, h, w, y + dy, x + dx,  visited));
      }
      return memo[{y,x}] = mx;
    }
    case '>': {
      if (visited.find({y, x + 1}) != visited.end()) return LOW_NUM;

      return memo[{y,x}] = 1 + dfsbt(grid, h, w, y, x + 1, visited);
    }
    case 'v': {
      if (visited.find({y + 1, x}) != visited.end()) return LOW_NUM;

      return memo[{y,x}] = 1 + dfsbt(grid, h, w, y + 1, x, visited);
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
  cout << dfsbt(grid, h, w, 0, startx, visited) << endl;

  return 0;
}
