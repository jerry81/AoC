#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string FNAME = "isolated.txt";

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

// could do dp if needed
int r(vector<int> rem, string &seq, int idx, char prev) {
  if (idx < 0) return (rem.empty() || rem[0] == 0);

  char cur_c = seq[idx];

  switch (cur_c) {
    case '#': {
      if (rem.empty()) return 0;

      if (rem.back() <= 0) return 0;

      rem[rem.size() - 1]--;
      return r(rem, seq, idx - 1, '#');
    }
    case '.': {
      if (!rem.empty() && prev == '#') {
        if (rem.back() != 0) return 0;

        rem.pop_back();
      }

      return r(rem, seq, idx - 1, '.');
    }
    default: {
      // can choose
      int sum = 0;
      vector<int> rem2 = rem;
      bool can_use_op = true; // '.'
      if (prev == '#') {
        if (rem.empty()) {
          can_use_op = false;
        } else if (rem.back() != 0) {
          can_use_op = false;
        }
      }
      if (!rem.empty()) rem.pop_back();
      bool can_use_brk = true;

      if (rem2.empty()) {
        can_use_brk = false;
      } else if (rem2.back() <= 0) {
        can_use_brk = false;
      }

      rem2[rem2.size()-1]--;

      if (can_use_op) sum+=r(rem, seq,idx-1, '.');

      if (can_use_brk) sum+=r(rem2, seq, idx-1, '#');
      return sum;
    }
      return 0;
  }
}

int main() {
  vector<string> lines = read_lines_into_vec();
  long long int res = 0;
  for (string l : lines) {
    vector<string> splBySpace = split_by(l, ' ');
    string layout = splBySpace[0];
    string grouping = splBySpace[1];
    vector<string> splByComma = split_by(grouping, ',');
    vector<int> ivals;
    for (string s : splByComma) ivals.push_back(stoi(s));
    // if (layout == "?###????????") {
    //   cout << "examining " << endl;
    //   int example = r(ivals, layout, layout.size()-1, ' ');
    //   cout << "out is " << example << endl;
    // }
    res += r(ivals, layout, layout.size() - 1, '.');
  }
  cout << "res is " << res << endl;
  // split lines
  return 0;
}