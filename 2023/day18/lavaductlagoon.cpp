#include <fstream>
#include <iostream>
#include <sstream>
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

vector<string> split_by(string s, char c) {
  vector<string> newTokens;
  istringstream strm(s);
  string tk;
  while (getline(strm, tk, c)) {
    newTokens.push_back(tk);
  }
  return newTokens;
}

int main() {
  vector<string> lines = read_lines_into_vec();
  pair<int, int> pt = {0, 0};
  pair<int, int> maxes = {0, 0};
  vector<vector<string>> instructions;
  for (auto line : lines) {
    vector<string> tokens = split_by(line, ' ');
    string d = tokens[0];
    int mag = stoi(tokens[1]);
    int dy = 0;
    int dx = 0;
    if (d == "U") {
      dy = -1 * mag;
    } else if (d == "R") {
      dx = mag;
    } else if (d == "D") {
      dy = mag;
    } else {
      dx = -1 * mag;
    }
    auto [y, x] = pt;
    pt = {y + dy, x + dx};
    auto [ny, nx] = pt;
    auto [my, mx] = maxes;
    maxes = {max(my, ny), max(mx, nx)};
    instructions.push_back(tokens);
  }
  auto [my, mx] = maxes;
  vector<vector<char>> grid(my+1, vector<char>(mx+1, '.'));
  pt = {0, 0};
    for (auto v: grid) {
    string str(v.begin(),v.end());
    cout <<  str << endl;;
  }
  for (auto instruction : instructions) {  // TODO: repetitive
    cout << "pt is " << get<0>(pt) << ","<< get<1>(pt)<< endl;
    string d = instruction[0];
    int mag = stoi(instruction[1]);
    int dy = 0;
    int dx = 0;
    if (d == "U") {
      dy = -1 * mag;
    } else if (d == "R") {
      dx = mag;
    } else if (d == "D") {
      dy = mag;
    } else {
      dx = -1 * mag;
    }
    auto [y, x] = pt;
    int ny = y + dy;
    int nx = x + dx;
    int miny = min(y, ny);
    int maxy = max(y,ny);
    int minx = min(x,nx);
    int maxx = max(x,nx);
    if (miny == maxy) {
      for (int i = minx; i <= maxx;++i) {
        cout << "ny " << ny << endl;
        cout << "i " << i << endl;
        grid[ny][i] = '#';
      }
    } else {
      for (int i = miny; i <= maxy; ++i) {
        cout << "nx " << nx << endl;
        cout << "i " << i << endl;
        grid[i][nx] = '#';
      }
    }
    pt = {ny,nx};
  }
  for (auto v: grid) {
    string str(v.begin(),v.end());
    cout <<  str << endl;;
  }

  return 0;
}
// get bounds of the
// first milestone:  print out the input map