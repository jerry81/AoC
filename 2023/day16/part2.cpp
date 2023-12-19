#include <fstream>
#include <iostream>
#include <set>
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

int get_count(tuple<int, int, int> start, vector<string> &lines, int &h,
              int &w) {
  set<tuple<int, int, int>> visited;
  vector<tuple<int, int, int>> current_beams;
  current_beams.push_back(start);
  while (!current_beams.empty()) {
    vector<tuple<int, int, int>> nxt_beams;
    for (auto [y, x, dir] : current_beams) {
      if (visited.find({y, x, dir}) != visited.end()) continue;

      visited.insert({y, x, dir});
      char cur = lines[y][x];

      vector<int> nxt_dirs;
      switch (cur) {
        case '.': {
          nxt_dirs.push_back(dir);
          break;
        }
        case '\\': {
          switch (dir) {
            case 0: {
              nxt_dirs.push_back(1);
              break;
            }
            case 1: {
              nxt_dirs.push_back(0);
              break;
            }
            case 2: {
              nxt_dirs.push_back(3);
              break;
            }
            default: {
              nxt_dirs.push_back(2);
            }
          }
          break;
        }
        case '/': {
          switch (dir) {
            case 0: {
              nxt_dirs.push_back(3);
              break;
            }
            case 1: {
              nxt_dirs.push_back(2);
              break;
            }
            case 2: {
              nxt_dirs.push_back(1);
              break;
            }
            default: {
              nxt_dirs.push_back(0);
            }
          }
          break;
        }
        case '-': {
          if (dir == 1 || dir == 3) {
            nxt_dirs.push_back(0);
            nxt_dirs.push_back(2);
          } else {
            nxt_dirs.push_back(dir);
          }
          break;
        }
        default: {  // |
          if (dir == 0 || dir == 2) {
            nxt_dirs.push_back(1);
            nxt_dirs.push_back(3);
          } else {
            nxt_dirs.push_back(dir);
          }
          break;
        }
      }
      for (int d : nxt_dirs) {
        int nx = x;
        int ny = y;
        switch (d) {
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

        if (nx < 0 || ny < 0) continue;

        if (ny >= h || nx >= w) continue;

        nxt_beams.push_back({ny, nx, d});
      }
    }
    current_beams = nxt_beams;
  }
  set<tuple<int, int>> counted;
  for (auto [a, b, _] : visited) {
    counted.insert({a, b});
  }
  return counted.size();
}

int main() {
   // directions 0 L 1 U 2 R 3 D
  vector<string> lines = read_lines_into_vec();
  int h = lines.size();
  int w = lines[0].size();
  int res = 0;
  for (int i = 0; i < w; ++i) {
    res = max(res, get_count({0,i,3},lines,h,w));
    res = max(res, get_count({h-1,i,1},lines,h,w));
  }

  for (int i = 0; i < h; ++i) {
    res = max(res, get_count({i,0,2}, lines, h, w));
    res = max(res, get_count({i,w-1,0}, lines, h, w));
  }

  cout << "res is " << res << endl;
  return 0;
}

/*

- vector<tuple<int,int,int>> paths
- store each position with its direction in hashset.
  - if same direction at a position is reached again then remove from paths
  - if goes off edge of map remove from paths.
- keep going while there are active paths.

*/