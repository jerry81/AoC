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

bool compareByMinOfZ(
    const pair<tuple<int, int, int>, tuple<int, int, int>>& a,
    const pair<tuple<int, int, int>, tuple<int, int, int>>& b) {
  int minOfThirdA = min(get<2>(a.first), get<2>(a.second));
  int minOfThirdB = min(get<2>(b.first), get<2>(b.second));
  return minOfThirdA < minOfThirdB;
}

int main() {
  vector<pair<tuple<int, int, int>, tuple<int, int, int>>> slabs_processed;

  vector<string> slabs = read_lines_into_vec();
  int mxy = 0;
  int mxx = 0;
  for (string s : slabs) {
    vector<string> tokens = split_by(s, '~');
    vector<string> tk1 = split_by(tokens[0], ',');
    vector<string> tk2 = split_by(tokens[1], ',');
    int x1 = stoi(tk1[0]);
    int y1 = stoi(tk1[1]);
    int x2 = stoi(tk2[0]);
    int y2 = stoi(tk2[1]);
    mxy = max(mxy, y1);
    mxy = max(mxy, y2);
    mxx = max(mxx, x1);
    mxx = max(mxx, x2);
    slabs_processed.push_back({{x1, y1, stoi(tk1[2])}, {x2, y2, stoi(tk2[2])}});
  }
  mxy += 1;
  mxx += 1;
  vector<vector<int>> heights(mxx, vector<int>(mxy, 0));

  sort(slabs_processed.begin(), slabs_processed.end(), compareByMinOfZ);
  // sort by min z
  for (auto [a, b] : slabs_processed) {
    auto [lx, ly, lz] = a;
    auto [hx, hy, hz] = b;
    int mxh = 0;
    for (int cx = lx; cx <= hx; ++cx) {
      for (int cy = ly; cy <= hy; ++cy) {
        mxh = max(heights[cx][cy], mxh);
      }
    }
    for (int cx = lx; cx <= hx; ++cx) {
      for (int cy = ly; cy <= hy; ++cy) {
        heights[cx][cy] = mxh + 1 + (hz - lz);
      }
    }
    cout << "slab low is " << lx << "," << ly << "," << lz << endl;
    cout << "slab high is " << hx << "," << hy << "," << hz << endl;
    for (int x = 0; x < mxx; ++x) {
      for (int y = 0; y < mxy; ++y) {
        cout << heights[x][y];
      }
      cout << "\n";
    }
  }

  // find max height for all the intersecting squares
  // push "down"
}