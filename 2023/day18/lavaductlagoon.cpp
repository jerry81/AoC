#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string FNAME = "input.txt"; // NORMALIZATION needed

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
// store points
int main() {
  int sum = 0;
  vector<string> lines = read_lines_into_vec();
  pair<int, int> pt = {0, 0};
  pair<int, int> maxes = {0, 0};
  pair<int,int> mins = {0,0};
  vector<vector<string>> instructions;

  for (auto line : lines) {
    vector<string> tokens = split_by(line, ' ');
    string d = tokens[0];
    int mag = stoi(tokens[1]);
    sum+=mag;
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
    auto [mny, mnx] = mins;
    maxes = {max(my, ny), max(mx, nx)};
    mins = {min(mny, ny), min(mnx, nx)};
    instructions.push_back(tokens);
  }
  auto [my, mx] = maxes;
  auto [mny,mnx] = mins;
  pair<int,int> normalized = {my + abs(mny), mx+abs(mnx)};
  auto [normy, normx] = normalized;
  pair<int,int> start = {abs(mny), abs(mnx)};
  vector<vector<char>> grid(get<0>(normalized)+1, vector<char>(get<1>(normalized)+1, '.'));
  pt = start;
  vector<pair<int,int>> points;
  for (auto instruction : instructions) {  // TODO: repetitive
    points.push_back(pt);
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
        grid[ny][i] = '#';
      }
    } else {
      for (int i = miny; i <= maxy; ++i) {
        grid[i][nx] = '#';
      }
    }
    pt = {ny,nx};
  }
  int shoelacesum = 0;
    for (int i = 0; i < points.size() - 1; ++i) {
        auto [y1, x1] = points[i];
        auto [y2, x2] = points[i + 1];

        cout << "point 1 is " << y1 << "," << x1 << endl;
        cout << "point 2 is " << y2 << "," << x2 << endl;

        int determ = x1 * y2;
        determ -= x2 * y1;
        shoelacesum += determ;
    }

    auto [y1, x1] = points.back();
    auto [y2, x2] = points.front();
    int determ = x1 * y2;
    determ -= x2 * y1;

    shoelacesum += determ;

    shoelacesum = abs(shoelacesum) / 2; // Take the absolute value and divide by 2 to get the area
    cout << "shoelacesum is " << shoelacesum << endl;

  // for (auto v: grid) {
  //   // string str(v.begin(),v.end());
  //   // cout << str << endl;
  //   bool count = false;
  //   bool can_off = false;
  //   int cursum = 0;
  //   for (char c: v) {

  //     if (count) {
  //       if (c == '.') {
  //         cursum++;
  //         can_off = true;
  //       } else {
  //         if (can_off) {
  //           sum+=cursum;
  //           cursum = 0;
  //           count = false;
  //           can_off = false;
  //         }
  //       }
  //     } else {
  //       if (c == '#') {
  //         count = true;
  //         can_off = false;
  //       }
  //     }

  //   }
  // }
  sum=sum/2+shoelacesum + 1;
  cout << "sum is now " << sum << endl;


  return 0;
}
// get bounds of the
// first milestone:  print out the input map
// fill logic:

// 54914 too high
// after accounting for not counting periods to the right of an unbounded #
// 45683 too low
// 47139 after some ridiculous hacking