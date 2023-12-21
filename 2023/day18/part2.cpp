#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string FNAME = "input.txt";  // NORMALIZATION needed

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

vector<long long int> transform(string inp) {
  long long int dir = (long long int) (inp[7] - '0');
  long long int todig = stoll(inp.substr(2, 5), nullptr, 16);
  return {todig, dir};
}

const vector<string> DIRECTION = {"R","D","L","U"};
// store points
int main() {
  long long int sum = 0;
  vector<string> lines = read_lines_into_vec();
  pair<long long int, long long int> pt = {0, 0};
  pair<long long int, long long int> maxes = {0, 0};
  pair<long long int, long long int> mins = {0, 0};
  vector<vector<long long int>> instructions;

  for (auto line : lines) {
    vector<string> tokens = split_by(line, ' ');
    // string d = tokens[0];
    // int mag = stoi(tokens[1]);
    vector<long long int> xform = transform(tokens[2]);
    string d = DIRECTION[xform[1]];
    long long int mag = xform[0];
    sum += mag;
    long long int dy = 0;
    long long int dx = 0;
    cout << "mag is " << mag << endl;
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
    cout << "push instruction " << xform[1] << ", "<< mag << endl;
    instructions.push_back({xform[1],mag});
  }
  cout << "done!" << endl;
  auto [my, mx] = maxes;
  auto [mny, mnx] = mins;
  pair<long long int, long long int> normalized = {my + abs(mny), mx + abs(mnx)};
  auto [normy, normx] = normalized;
  pair<long long int, long long int> start = {abs(mny), abs(mnx)};
  // vector<vector<char>> grid(get<0>(normalized) + 1,
  //                           vector<char>(get<1>(normalized) + 1, '.'));
  pt = start;
  cout << "next loop coming " << endl;
  vector<pair<long long int, long long int>> points;
  for (auto instruction : instructions) {  // TODO: repetitive
    points.push_back(pt);
    int d = instruction[0];
    long long int mag = instruction[1];
    long long int dy = 0;
    long long int dx = 0;
    cout << "mag is " << mag << endl;
    if (d == 3) {
      dy = -1 * mag;
    } else if (d == 0) {
      dx = mag;
    } else if (d == 1) {
      dy = mag;
    } else {
      dx = -1 * mag;
    }
    auto [y, x] = pt;
    long long int ny = y + dy;
    long long int nx = x + dx;
    cout << "dy " << dy << endl;
    cout << "dx " << dx << endl;
    cout << "ny " << ny << endl;
    cout << "nx " << nx << endl;
    long long int miny = min(y, ny);
    long long int maxy = max(y, ny);
    long long int minx = min(x, nx);
    long long int maxx = max(x, nx);
    // if (miny == maxy) {
    //   for (int i = minx; i <= maxx; ++i) {
    //     grid[ny][i] = '#';
    //   }
    // } else {
    //   for (int i = miny; i <= maxy; ++i) {
    //     grid[i][nx] = '#';
    //   }
    // }
    pt = {ny, nx};
  }
  cout << "pts size " << points.size() << endl;
  long long int shoelacesum = 0;
  for (int i = 0; i < points.size() - 1; ++i) {
    auto [y1, x1] = points[i];
    auto [y2, x2] = points[i + 1];
    cout << "point is " << y1 <<","<<x1 << endl;
    cout << "points 2 is " << y2 << ","<<x2 << endl;
    long long int determ = x1 * y2;
    determ -= x2 * y1;
    cout << "determ is " << determ << endl;
    shoelacesum += determ;
  }

  auto [y1, x1] = points.back();
  auto [y2, x2] = points.front();
  long long int determ = x1 * y2;
  determ -= x2 * y1;

  shoelacesum += determ;

  shoelacesum = abs(shoelacesum) /
                2;  // Take the absolute value and divide by 2 to get the area
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
  sum = sum / 2 + shoelacesum + 1;
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