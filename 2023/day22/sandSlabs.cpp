#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
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
  int result = 0;
  vector<string> slabs = read_lines_into_vec();
  int mxy = 0;
  int mxx = 0;
  int mxz = 0;
  for (string s : slabs) {
    vector<string> tokens = split_by(s, '~');
    vector<string> tk1 = split_by(tokens[0], ',');
    vector<string> tk2 = split_by(tokens[1], ',');
    int x1 = stoi(tk1[0]);
    int y1 = stoi(tk1[1]);
    int x2 = stoi(tk2[0]);
    int y2 = stoi(tk2[1]);
    int z1 = stoi(tk1[2]);
    int z2 = stoi(tk2[2]);
    mxy = max(mxy, y1);
    mxy = max(mxy, y2);
    mxx = max(mxx, x1);
    mxx = max(mxx, x2);
    mxz = max(mxz, z1);
    mxz = max(mxz, z2);
    slabs_processed.push_back({{x1, y1, z1}, {x2, y2, z2}});
  }
  mxy += 1;
  mxx += 1;
  vector<vector<int>> heights(mxx, vector<int>(mxy, 0));

  sort(slabs_processed.begin(), slabs_processed.end(), compareByMinOfZ);

  vector<pair<tuple<int, int, int>, tuple<int, int, int>>> slabs_processed2;

  vector<vector<vector<int>>> cube(
      mxx + 1, vector<vector<int>>(mxy + 1, vector<int>(mxz + 1, -1)));

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

    int nlz = mxh + 1;
    int nhz = nlz + (hz - lz);

    slabs_processed2.push_back({{lx, ly, nlz}, {hx, hy, nhz}});

    for (int x = lx; x <= hx; ++x) {
      for (int y = ly; y <= hy; ++y) {
        for (int z = nlz; z <= nhz; ++z) {
          cube[x][y][z] = slabs_processed2.size() - 1;
        }
      }
    }
  }

  int cur_idx = 0;
  for (auto [a, b] : slabs_processed2) {
    auto [lx, ly, lz] = a;
    auto [hx, hy, hz] = b;

    unordered_set<int> above_blocks;
    int idx_above = hz + 1;
    if (idx_above >= mxz) {
      result++;
      continue;
    }

    for (int x = lx; x <= hx; ++x) {
      for (int y = ly; y <= hy; ++y) {
        int above_owner = cube[x][y][idx_above];
        if (above_owner >= 0 && above_owner != cur_idx) above_blocks.insert(above_owner);
      }
    }
    if (above_blocks.empty()) {
      cout << "cur_idx is valid " << cur_idx << endl;
      result++;
      continue;
    }
    bool ok = true;
    for (auto item : above_blocks) {
      auto [a, b] = slabs_processed2[item];
      // get count of items below slab
      auto [lx, ly, lz] = a;
      auto [hx, hy, hz] = b;
      int below_idx = lz-1;
      if (below_idx < 1) continue;
      unordered_set<int> below_blocks;
      for (int x = lx; x <=hx; ++x) {
        for (int y = ly; y <=hy; ++y) {
          int below_owner = cube[x][y][below_idx];
           if (below_owner >= 0 && below_owner != cur_idx) below_blocks.insert(below_owner);
        }
      }
      if (below_blocks.empty()) {
        ok=false;
        break;
      }
    }
    if (ok) {
      cout << cur_idx << " is valid " << endl;
      result++;
    }

    cur_idx++;
  }
  cout << "result " << result << endl;
  //   for (int x = 0; x < mxx; ++x) {
  //   for (int y = 0; y < mxy; ++y) {
  //     cout << heights[x][y];
  //   }
  //   cout << "\n";
  // }

  // find max height for all the intersecting squares
  // push "down"
  // finally, how do we check blocks that would "fall"
  // examine one layer above surface area of block
  // list of blocks
  // for each block above, check minus block removed, if its surface area has a
  // block below.
}