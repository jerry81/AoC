#include <fstream>
#include <iostream>
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

long long int horizontalCheck(vector<string> lines) {
  vector<int> nextcandidates;
  for (auto b : lines) {
    // line of a grid
    int len = b.size();
    if (nextcandidates.empty()) {
      for (int i = 0; i < len - 1; ++i) {
        char c = b[i];
        char d = b[i + 1];
        if (c == d) {
          nextcandidates.push_back(i);
        }
      }
    } else {
      vector<int> nextnextcandds;
      for (int i : nextcandidates) {
        if (b[i] == b[i + 1]) nextnextcandds.push_back(i);
      }
      nextcandidates = nextnextcandds;
    }
  }
   if (nextcandidates.size() == 1) return nextcandidates[0];
    return -1;
}

long long int verticalCheck(vector<string> lines) {
  vector<int> nextcandidates;
  int ht = lines.size();
  // line of a grid
  int wd = lines[0].size();
  for (int i = 0; i < wd; ++i) {
    if (nextcandidates.empty()) {
      for (int j = 0; j < ht - 1; ++j) {
        if (lines[j][i] == lines[j+1][i]) {
          nextcandidates.push_back(j);
        }
      }
    } else {
      vector<int> nxtnxt;
      for (int j: nextcandidates) {
        if (lines[j][i] == lines[j+1][i]) nxtnxt.push_back(j);

        nextcandidates = nxtnxt;
      }
    }
  }
  if (nextcandidates.size() == 1) return nextcandidates[0];
  return -1;
}


int main() {
  vector<string> all_lines = read_lines_into_vec();
  vector<vector<string>> grids;
  vector<string> cur_grid;
  for (string s : all_lines) {
    if (s.find('#') == string::npos && s.find('.') == string::npos) {
      grids.push_back(cur_grid);
      cur_grid.clear();
    } else {
      cur_grid.push_back(s);
    }
  }
  grids.push_back(cur_grid);
  long long int res;
  for (auto a : grids) {
    long long int sum = 0;
    int hres = horizontalCheck(a);
    if (hres >=0) sum+= 100*hres;
    int vres = verticalCheck(a);
    if (vres >= 0) sum+= vres;
    cout << "sum is " << sum << endl;
    res+= sum;
  }
  cout << "res is " << res << endl;
  return 0;
}