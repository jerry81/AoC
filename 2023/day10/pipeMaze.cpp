#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const string FNAME = "sm.txt";

string to_h(pair<int, int> pos) {
  auto [f, s] = pos;
  return to_string(f) + "," + to_string(s);
}

pair<int,int> to_pos(string s) {
  auto pos = s.find(',');
  return {stoi(s.substr(0,pos)), stoi(s.substr(pos+1))};
}

unordered_map<string, int> dists;
vector<vector<string>> paths;
vector<pair<int,int>> MOVES = {
  {-1,0}, // U
  {0,1}, // R
  {1,0}, // D
  {0,-1} // L
};

void findLoop(pair<int,int> pos, vector<string> accum, int& h, int& w, vector<string>& grid, bool isFirstMove) {
  string prev = "";
  auto [cy, cx] = pos;
  if (cy < 0) return;
  if (cx < 0) return;
  if (cy >= h) return;
  if (cx >= w) return;
  char cur_char = grid[cy][cx];

  if (!accum.empty()) prev = accum.back();
  for (auto [dy,dx]: MOVES) {
    int nr = dy + cy;
    int nc = dx + cx;
    switch (cur_char) {
      case '|': {
      } case '-': {
      } case 'J': {
      } case '7': {
      } case 'L': {
      } default: {
      }
    }
  }
}

int main() {
  string hsh = to_h({15, 300});
  pair<int,int> pr = to_pos(hsh);
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
  // we have a grid
  // we have start position
  // dfs to start
}