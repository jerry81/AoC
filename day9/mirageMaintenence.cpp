#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const string FNAME = "input.txt";

int main() {
  long long int sm = 0;
  ifstream strm(FNAME);
  string line;

  while (getline(strm, line)) {
    vector<vector<int>> stk;
    vector<int> items;
    istringstream spaceStream(line);
    string spaceToken;
    while (spaceStream >> spaceToken) {
      items.push_back(stoi(spaceToken));
    }
    stk.push_back(items);
    bool all_zeros = false;
    while (!all_zeros) {
      vector<int> cur_line;
      all_zeros = true;
      vector<int> analyzed = stk.back();
      for (int i = 0; i < analyzed.size()-1;++i) {
        int it1=analyzed[i];
        int it2=analyzed[i+1];
        int diff = it2 - it1;
        cur_line.push_back(diff);
        if (diff != 0) all_zeros = false;
      }
      stk.push_back(cur_line);
    }
    // we have a stk.  now add an item to the end;
    int prev = 0;
    while (!stk.empty()) {
      vector<int> cur = stk.back();
      stk.pop_back();
      int ender = cur.back() + prev;
      prev = ender;
    }
    sm+=prev;
  }
  cout << "sum " << sm << endl;
  return 0;
}