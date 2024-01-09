#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

const string FNAME = "input.txt";

struct Hail {
  tuple<long long int, long long int, long long int> pos;
  tuple<long long int, long long int, long long int> vel;
  void print() {
    cout << "printing hail! " << endl;
    cout << "pos is " << endl;
    cout << get<0>(pos) << " " << get<1>(pos) << " " << get<2>(pos) << endl;
    cout << "vel is " << endl;
    cout << get<0>(vel) << " " << get<1>(vel) << " " << get<2>(vel) << endl;
  }
};

vector<string> split_by_str(string s, string delim) {
  size_t pos = 0;
  string token1;  // define a string variable
  vector<string> res;
  while ((pos = s.find(delim)) != std::string::npos) {
    token1 = s.substr(0, pos);  // store the substring
    res.push_back(token1);
    s.erase(0, pos + delim.length()); /* erase() function store the current
                                         positon and move to next token. */
  }
  res.push_back(s);
  return res;
}

vector<string> read_lines_into_vec() {
  ifstream strm(FNAME);
  string line;
  vector<string> lines;
  while (getline(strm, line)) {
    lines.push_back(line);
  }
  return lines;
}

unordered_set<int> crossed;
// const long long int MIN = 7;
// const long long int MAX = 27;
const long long int MIN = 2e14;
const long long int MAX = 4e14;

long double intersect(Hail h1, Hail h2) {
  long double time;
  auto [xa, ya, _] = h1.pos;
  auto [xb, yb, __] = h2.pos;
  auto [dxa, dya, ___] = h1.vel;
  auto [dxb, dyb, ____] = h2.vel;
  long double m = (long double) ((long double)dya / (long double)dxa);  // 1
  long double b = (long double) ((long double)ya - (m * (long double)xa));
  // slope is dya / dxa
  // we want intercept top and bottom

  long double n = (long double) ((long double)dyb / (long double)dxb);
  long double c = (long double)((long double)yb - ((long double)(n * (long double)xb)));

  long double x = (c - b) / (m - n);
  long double y = (m * x) + b;

  // cout << "n " << n << endl;
  // cout << "m " << m << endl;



  time = (y - ya) / dya;
  long double time2 = (y - yb) / dyb;
  bool valid = (long double)x >= MIN && (long double)x <= MAX &&
               (long double)y >= MIN && (long double)y <= MAX && time2 >= 0;
  return valid ? time : -1;
}

vector<tuple<int, int, long double>> intersections;

static bool compareIntersections(tuple<int, int, long double> a, tuple<int, int, long double> b) {
  return get<2>(a) < get<2>(b);
}
int main() {
  vector<string> inp = read_lines_into_vec();
  vector<Hail> hails;
  for (string s : inp) {
    vector<string> tokens = split_by_str(s, "@");
    string t1 = tokens[0];
    string t2 = tokens[1];
    Hail h;
    vector<string> t1s = split_by_str(t1, ", ");
    vector<string> t2s = split_by_str(t2, ", ");
    h.pos = {stoll(t1s[0]), stoll(t1s[1]), stoll(t1s[2])};
    h.vel = {stoll(t2s[0]), stoll(t2s[1]), stoll(t2s[2])};
    hails.push_back(h);
  }
  int sz = hails.size();
  int res = 0;
  for (int i = 0; i < sz - 1; ++i) {
    Hail a = hails[i];

    for (int j = i + 1; j < sz; ++j) {
      long double t = intersect(a, hails[j]);
      if (t >= 0) {
        intersections.push_back({i, j, t});
      }
    }
  }

  sort(intersections.begin(), intersections.end(), compareIntersections);
  for (auto [a,b,_] : intersections) {
    // if (crossed.find(a) != crossed.end()) continue;
    // if (crossed.find(b) != crossed.end()) continue;

    res++;
  }

  cout << res << endl;

  return 0;
}

/*

150 too low

*/