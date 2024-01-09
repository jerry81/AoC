#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

const string FNAME = "sm.txt";

struct Hail {
  tuple<int, int, int> pos;
  tuple<int, int, int> vel;
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

const long long int MIN = 7;
const long long int MAX = 27;
bool intersect(Hail h1, Hail h2) {
  auto [xa, ya, _] = h1.pos;
  auto [xb, yb, __] = h2.pos;
  auto [dxa, dya, ___] = h1.vel;
  auto [dxb, dyb, ____] = h2.vel;
  double m = (double) dya / (double) dxa; // 1
  double b =  ya - (m*(double)xa);
  // slope is dya / dxa
  // we want intercept top and bottom

  double n = (double) dyb / (double) dxb;
  double c = yb - (n*(double)xb);

  double x = (c-b) / (m-n);
  double y = (m*x) + b;
  bool res = x > MIN && x <= MAX && y > MIN && y <= MAX;
  return res;
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
    h.pos = {stoi(t1s[0]), stoi(t1s[1]), stoi(t1s[2])};
    h.vel = {stoi(t2s[0]), stoi(t2s[1]), stoi(t2s[2])};
    hails.push_back(h);
  }
  int sz = hails.size();
  int res = 0;
  for (int i = 0; i < sz - 1; ++i) {
    Hail a = hails[i];

    for (int j = i + 1; j < sz; ++j) {
      if (crossed.find(j) != crossed.end()) continue;
      if (crossed.find(i) != crossed.end()) continue;

      if (intersect(a, hails[j])) {
        crossed.insert(i);
        crossed.insert(j);
        res++;

      }
    }
  }
  cout << res << endl;
  return 0;
}