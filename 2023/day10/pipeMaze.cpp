#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include <vector>

using namespace std;

const string FNAME = "input.txt";

long long int counter = 0;

string to_h(pair<int, int> pos) {
  auto [f, s] = pos;

  return to_string(f) + "," + to_string(s);
}

string d_to_h(pair<int,int> pos, char direction) {
  return to_h(pos) + ","+string(1,direction);
}

pair<int, int> to_pos(string s) {
  auto pos = s.find(',');
  return {stoi(s.substr(0, pos)), stoi(s.substr(pos + 1))};
}

unordered_map<string, int> dists;
vector<vector<string>> paths;
unordered_map<char, pair<int, int>> MOVES = {
    {'U', {-1, 0}},  // U
    {'R', {0, 1}},   // R
    {'D', {1, 0}},   // D
    {'L', {0, -1}}   // L
};

unordered_set<string> visited;

void findLoop(pair<int, int> pos, vector<string> accum, int& h, int& w,
              vector<string>& grid, string& startS) {
  string prev = "";
  auto [cy, cx] = pos;

  if (cy < 0) return;
  if (cx < 0) return;
  if (cy >= h) return;
  if (cx >= w) return;
  string curS = to_h(pos);


  if (!accum.empty()) prev = accum.back();

  if (!empty(prev) && curS == startS) {
    paths.push_back(accum);
    return;
  }
  char cur_char = grid[cy][cx];
  if (cur_char == '.') return;
  for (auto [direction, newpos] :
       MOVES) {  // direction is current move direction from cur to nxt
    auto [dy, dx] = newpos;
    int nr = dy + cy;
    int nc = dx + cx;
    if (nr < 0) continue;
    if (nc < 0) continue;
    if (nr >= h) continue;
    if (nc >= w) continue;

    string nxt_as_h = to_h({nr, nc});
    if (prev == nxt_as_h) continue;  // dont move backwards

    string str = d_to_h({nr,nc}, direction);
    if (visited.find(str) != visited.end()) {
      return;
    }

    visited.insert(str);
    char nxt_char = grid[nr][nc];
    if (nxt_char == '.') continue;
    vector<string> accum_cpy = accum;
    switch (cur_char) {
      case '.': { break; }
      case 'S': {
        if (direction == 'L') {
          if (nxt_char == 'J' || nxt_char == '7' || nxt_char == '|') break;
        } else if (direction == 'R') {
          if (nxt_char == 'L' || nxt_char == '|' || nxt_char == 'F') break;
        } else if (direction == 'U') {
          if (nxt_char == '-' || nxt_char == 'L' || nxt_char == 'J') break;
        } else {
          if (nxt_char == '-' || nxt_char == 'F' || nxt_char == '7') break;
        }
        accum_cpy.push_back(curS);
        findLoop({nr, nc}, accum_cpy, h, w, grid, startS);
        break;
      }
      case '|': {
        // DOWN and UP -> '|'
        // UP -> '7', 'F'
        // DOWN -> 'J', 'L'
        if (direction == 'L' || direction == 'R') break;
        if (direction == 'U') {
          if (nxt_char == 'L' || nxt_char == 'J') break;
        } else if (direction == 'D') {
          if (nxt_char == 'F' || nxt_char == '7') break;
        }
        accum_cpy.push_back(curS);
        findLoop({nr, nc}, accum_cpy, h, w, grid, startS);
        break;
      }
      case '-': {
        if (direction == 'U' || direction == 'D') break;
        if (direction == 'L') {
          if (nxt_char == 'J' || nxt_char == '7') break;
        } else if (direction == 'R') {
          if (nxt_char == 'F' || nxt_char == 'L') break;
        }
        accum_cpy.push_back(curS);
        findLoop({nr, nc}, accum_cpy, h, w, grid, startS);

        break;
      }
      case 'J': {
        if (direction != 'U' && direction != 'L') break;
        if (direction == 'U') {
          if (nxt_char == 'L' || nxt_char == 'J') break;
        } else if (direction == 'L') {
          if (nxt_char == 'J' || nxt_char == '7') break;
        }
        accum_cpy.push_back(curS);
        findLoop({nr, nc}, accum_cpy, h, w, grid, startS);
        break;
      }
      case '7': {
        if (direction != 'L' && direction != 'D') break;
        if (direction == 'L') {
          if (nxt_char == 'J' || nxt_char == '7') break;
        } else if (direction == 'D') {
          if (nxt_char == 'F' || nxt_char == '7') break;
        }
        accum_cpy.push_back(curS);
        findLoop({nr, nc}, accum_cpy, h, w, grid, startS);
        break;
      }
      case 'L': {
        if (direction != 'R' && direction != 'U') break;
        if (direction == 'R') {
          if (nxt_char == 'F' || nxt_char == 'L') break;

        } else if (direction == 'U') {
          if (nxt_char == 'J' || nxt_char == 'L') break;
        }
        accum_cpy.push_back(curS);
        findLoop({nr, nc}, accum_cpy, h, w, grid, startS);
        break;
      }
      default: {  // 'F'
        if (direction != 'R' && direction != 'D') break;
        if (direction == 'R') {
          if (nxt_char == 'F' || nxt_char == 'L') break;

        } else if (direction == 'D') {
          if (nxt_char == 'F' || nxt_char == '7') break;
        }
        accum_cpy.push_back(curS);
        findLoop({nr, nc}, accum_cpy, h, w, grid, startS);
      }
    }
  }
}

int main() {
  string hsh = to_h({15, 300});
  pair<int, int> pr = to_pos(hsh);
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
  cout << "height is " << height << endl;;
  cout << "width is " << width << endl;
  auto [f, s] = start;
  string starthsh = to_h(start);
  cout << "start is at " << starthsh << endl;
  findLoop(start, {}, width, height, grid, starthsh);
  cout << "size is " << paths.size() << endl;
  cout << "ans is " << paths[0].size() / 2;
  return 0;
  // we have a grid
  // we have start position
  // dfs to start
}