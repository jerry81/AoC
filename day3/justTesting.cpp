#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct GridToken {
  int r = 0;
  int cs = 0;
  int ce = 0;
  int val = 0;
};
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
  }

  long long res = 0;

  for (GridToken g: tokens) {
    int r = g.r;
    for (int i = g.cs; i <= g.ce; ++i) {
      bool hasSymbol = false;
      // check neighbors of grid[r][i];
      for (auto [dy,dx]: EIGHT_D) {
        int nr = r+dy;
        int nc = i+dx;
        if (nr < 0 || nr >=grid[r].size()) continue;
        if (nc < 0 || nc >= grid[r].size()) continue;
        char test = grid[nr][nc];
        if (test != '.' && !isdigit(test)) {
          hasSymbol = true;
          break;
        }
      }
      if (hasSymbol) {
        cout << "adding " << g.val << endl;
        res+=g.val;
        break;
      }
    }
  }

  cout << "res is " << res << endl;

  return 0;
}