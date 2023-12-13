#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
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

string unfold(string inp, bool grouping = false) {
  string ret = "";
  string seperator = grouping ? "," : "?";
  for (int i = 0; i < 5; ++i) {
    ret += inp;
    ret += seperator;
  }
  ret.pop_back();
  return ret;
}

map<tuple<int,int,int,char>, long long int> memo;

// could do dp if needed
long long int r(vector<int> rem, string &seq, int idx, char prev) {
  int sz = rem.size();
  int bk = rem.empty() ? -1: rem.back();
  //  cout << "hsh is " << hsh << endl;

  if (idx < 0) {
    // return rem.empty() || (!rem.empty() && rem[0] == 0);
    return (rem.empty() || (!rem.empty() && rem[0] == 0)) ? 1 : 0;
  }


  const tuple<int,int,int,char> hsh = tuple(sz, idx, bk, prev);
  if (memo.find(hsh) != memo.cend()) return memo[hsh];


  char cur_c = seq[idx];

  switch (cur_c) {
    case '#': {
      if (rem.empty()) {
        memo[hsh] = 0;
        return 0;
      }

      if (!rem.empty() && rem.back() <= 0) {
        memo[hsh] = 0;
        return 0;
      }

      rem[rem.size() - 1]--;

      return r(rem, seq, idx - 1, '#');
    //  memo[hsh] = r(rem, seq, idx - 1, '#');
    //  return memo[hsh];
    }
    case '.': {
      if (!rem.empty() && prev == '#') {
        if (rem.back() != 0) {
          memo[hsh] = 0;
          return 0;
        }

        rem.pop_back();
      }
      // if (memo.find(curhsh2) != memo.end()) return memo[curhsh2];
      return r(rem, seq, idx - 1, '.');
      //  memo[hsh] = r(rem, seq, idx - 1, '.');
      //  return memo[hsh];
    }
    default: {
      // can choose
      int sum = 0;
      vector<int> rem2 = rem;
      bool can_use_op = true;  // '.'
      if (prev == '#') {
        if (rem.empty()) {
          can_use_op = false;
        } else if (rem.back() != 0) {
          can_use_op = false;
        }
      }
      if (!rem.empty() && rem.back() == 0) {
        rem.pop_back();
      }
      bool can_use_brk = true;

      if (rem2.empty()) {
        can_use_brk = false;
      } else {
        if (rem2.back() <= 0) can_use_brk = false;

        rem2[rem2.size() - 1]--;
      }

      if (can_use_op) {
        // string curhsh = h(rem, idx - 1, '.');

        // // if (memo.find(curhsh) != memo.end()) {
        //   sum += memo[curhsh];
        // } else {
          sum += r(rem, seq, idx - 1, '.');
        // }
      }

      if (can_use_brk) {
        // string hsh3 = h(rem2, idx-1, '#');
        // memo[hsh3] =  r(rem2, seq, idx - 1, '#');
        // sum+= memo[hsh3];
        // string curhsh = h(rem2, idx - 1, '#');
        // if (memo.find(curhsh) != memo.end()) {
        //   sum += memo[curhsh];
        // } else {
          sum += r(rem2, seq, idx - 1, '#');
        // }
      }

    //  if (sum == 0) memo[hsh] = 0;
      // memo[hsh] = sum;
      // return sum;
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
    layout = unfold(layout);
    grouping = unfold(grouping, true);
    cout << "layout is " << layout << endl;
    cout << "grouping is " << grouping << endl;
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