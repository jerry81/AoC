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

unordered_map<char, pair<int, int>> MOVES = {
    {'U', {-1, 0}},  // U
    {'R', {0, 1}},   // R
    {'D', {1, 0}},   // D
    {'L', {0, -1}}   // L
};

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
  pair<int, int> cur = {128, 37};
  char dir = 'R';
  cout << "start.first " << start.first << endl;;
  cout << "start.second " << start.second << endl;;
  while (cur.first != start.first || cur.second != start.second) {
    char cur_c = grid[cur.first][cur.second];
    counter++;
    if (cur_c == 'J') {
      if (dir == 'R') {
        cur.first--;
        dir = 'U';
      } else {
        cur.second--;
        dir = 'L';
      }

    } else if (cur_c == 'F') {
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
      if (dir == 'D') {
        cur.second++;
        dir = 'R';
      } else {
        cur.first--;
        dir = 'U';
      }
    } else if (cur_c == '7') {
      if (dir == 'R') {
        cur.first++;
        dir = 'D';
      } else {
        cur.second--;
        dir = 'L';
      }
    }
  }
  cout << "cnt is " << counter << endl;
  return 0;
  // we have a grid
  // we have start position
  // dfs to start
}