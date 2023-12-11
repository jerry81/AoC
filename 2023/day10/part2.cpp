#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const string FNAME = "input.txt";

long long int counter = 1;

string to_h(pair<int, int> pos) {
  auto [f, s] = pos;

  return to_string(f) + "," + to_string(s);
}
struct Bounds {
  int x1;
  int x2;
  int y1;
  int y2;
};

vector<Bounds> edges;

unordered_map<char, pair<int, int>> MOVES = {
    {'U', {-1, 0}},  // U
    {'R', {0, 1}},   // R
    {'D', {1, 0}},   // D
    {'L', {0, -1}}   // L
};

bool intersects(int sy, int sx, Bounds b) {
  // just horizontal line, increasing x
  int mny = min(b.y1, b.y2);
  int mxy = max(b.y1, b.y2);
  int mnx = min(b.x1, b.x2);
  int mxx = max(b.x1, b.x2);
  if (mny == mxy) return false;

  if (sy < mny) return false;
  if (sy > mxy) return false;
  if (sx > mxx) return false;

  return true;
}

int main() {
  pair<int, int> start;
  ifstream strm(FNAME);
  string line;
  vector<string> grid;
  int width = 0;
  int height = 0;
  int row = 0;
  while (getline(strm, line)) {
    height++;
    grid.push_back(line);
    width = line.size();
    auto pos = line.find('S');
    if (pos != string::npos) {
      start = {row, pos};
    }
    row++;
  }
  auto [f, s] = start;
  Bounds current_bounds;

   pair<int, int> cur = {128, 37};
  // pair<int, int> cur = {1, 2};
  // pair<int, int> cur = {2, 1};

  current_bounds.x1 = s;
  current_bounds.y1 = f;

  unordered_set<string> in_path;
  in_path.insert(to_h(start));

  char dir = 'R';
  cout << "start.first " << start.first << endl;
  cout << "start.second " << start.second << endl;
  while (cur.first != start.first || cur.second != start.second) {
    char cur_c = grid[cur.first][cur.second];
      in_path.insert(to_h(cur));

    counter++;
    if (cur_c == 'J') {
      current_bounds.y2 = cur.first;
      current_bounds.x2 = cur.second;
      edges.push_back(current_bounds);
      current_bounds.y1 = cur.first;
      current_bounds.x1 = cur.second;
      if (dir == 'R') {
        cur.first--;
        dir = 'U';
      } else {
        cur.second--;
        dir = 'L';
      }

    } else if (cur_c == 'F') {
      current_bounds.y2 = cur.first;
      current_bounds.x2 = cur.second;
      edges.push_back(current_bounds);
      current_bounds.y1 = cur.first;
      current_bounds.x1 = cur.second;
      if (dir == 'U') {
        cur.second++;
        dir = 'R';
      } else {
        cur.first++;
        dir = 'D';
      }
    } else if (cur_c == '|') {
      if (dir == 'D') {
        cur.first++;

      } else {
        cur.first--;
      }
    } else if (cur_c == '-') {
      if (dir == 'R') {
        cur.second++;
      } else {
        cur.second--;
      }
    } else if (cur_c == 'L') {
      current_bounds.y2 = cur.first;
      current_bounds.x2 = cur.second;
      edges.push_back(current_bounds);
      current_bounds.y1 = cur.first;
      current_bounds.x1 = cur.second;
      if (dir == 'D') {
        cur.second++;
        dir = 'R';
      } else {
        cur.first--;
        dir = 'U';
      }
    } else if (cur_c == '7') {
      current_bounds.y2 = cur.first;
      current_bounds.x2 = cur.second;
      edges.push_back(current_bounds);
      current_bounds.y1 = cur.first;
      current_bounds.x1 = cur.second;
      if (dir == 'R') {
        cur.first++;
        dir = 'D';
      } else {
        cur.second--;
        dir = 'L';
      }
    }
  }
  current_bounds.y2 = start.first;
  current_bounds.x2 = start.second;
  edges.push_back(current_bounds);
  int boundeds = 0;

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (in_path.find(to_h({i,j})) != in_path.end()) continue;
      int intersections = 0;
      for (Bounds b : edges) {
        if (intersects(i, j, b)) {
          //  if (i == 2 && j == 2) cout << "intersection with " << b.y1 << " ,
          //  " << b.y2 << " , " << b.x1 << " , " << b.x2 << endl;
          intersections++;
        }
      }
      if (intersections % 2 == 1) {
        boundeds++;
      }
    }
  }
  cout << "there are " << edges.size() << " edges " << endl;
  cout << "cnt is " << counter << endl;
  cout << "intersections is " << boundeds << endl;
  return 0;
  // we have a grid
  // we have start position
  // dfs to start
}

/*

get all "sides"
when hitting a "corner" a bounds will be added, and a new bounds is created
use raycast to find if enclosed - odd intersectins means inside

*/