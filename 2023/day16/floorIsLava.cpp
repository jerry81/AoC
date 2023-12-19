#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <set>

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

int main () {
  set<tuple<int,int,int>> visited; // directions 0 L 1 U 2 R 3 D
  vector<string> lines = read_lines_into_vec();
  int h = lines.size();
  int w = lines[0].size();
  vector<tuple<int,int,int>> current_beams;
  auto start = make_tuple(0,0,2);
  current_beams.push_back(start);
  while (!current_beams.empty()) {
    vector<tuple<int,int,int>> nxt_beams;
    for (auto [y,x,dir]: current_beams) {
      if (visited.find({y,x,dir}) == visited.end()) continue;

      visited.insert({y,x,dir});
      int nx = x;
      int ny = y;
      switch (dir) {
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
    }
  }
  return 0;
}

/*

- vector<tuple<int,int,int>> paths
- store each position with its direction in hashset.
  - if same direction at a position is reached again then remove from paths
  - if goes off edge of map remove from paths.
- keep going while there are active paths.

*/