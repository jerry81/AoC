#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct GridToken {
  int r = 0;
  int cs = 0;
  int ce = 0;
  int val = 0;
};
string get_h(int r, int c) {
  return to_string(r)+","+to_string(c);
}
int main() {
 vector<string> grid = {
  "467..114..",
"...*......",
"..35..633.",
"......#...",
"617*......",
".....+.58.",
"..592.....",
"......755.",
"...$.*....",
".664.598.."
};

  vector<pair<int,int>> EIGHT_D = {{1,1},{-1,1},{1,-1},{-1,-1}, {0,1}, {1,0}, {0,-1}, {-1,0}};
  vector<GridToken> tokens;
  unordered_map<string, vector<int>> gears;
  // get a list of numbers with row, cols cole, number;
  for (int i = 0; i < grid.size(); ++i) {
    string r = grid[i];
    string cur_n = "";
    for (int j = 0; j < r.size(); ++j) {
      char c = r[j];

      if (isdigit(c)) {
        cur_n+=string(1,c);
      } else {
        if (!cur_n.empty()) {
          GridToken g;
          g.val = stoi(cur_n);
          g.r = i;
          g.ce = j-1;
          g.cs = j-cur_n.size();
          tokens.push_back(g);
          cur_n = "";
        }
      }
    }
      if (!cur_n.empty()) {
      GridToken g;
      g.val = stoi(cur_n);
      g.r = i;
      g.ce = r.size()-1;
      g.cs = g.ce-cur_n.size();
      tokens.push_back(g);
    }

  }


  long long int res = 0;

  for (GridToken g: tokens) {
    int r = g.r;
     unordered_set<string> visited;
    for (int i = g.cs; i <= g.ce; ++i) {

      // check neighbors of grid[r][i];
      for (auto [dy,dx]: EIGHT_D) {
        int nr = r+dy;
        int nc = i+dx;
        if (nr < 0 || nr >=grid[r].size()) continue;
        if (nc < 0 || nc >= grid[r].size()) continue;
        char test = grid[nr][nc];
        string hsh = get_h(nr,nc);
        if (test == '*' && visited.find(hsh) == visited.end()) {

          gears[hsh].push_back(g.val);
          visited.insert(hsh);
        }
      }

    }

  }

  for (auto [k,v]: gears) {
    cout << "k is " << k << "v.size is " << v.size() << endl;
    if (v.size() ==2) {
      res+=(long long int) v[0]*v[1];
    }
  }

  cout << "res is " << res << endl;

  return 0;
}