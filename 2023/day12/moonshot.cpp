#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const string FNAME = "sm.txt";

string h(vector<int> rem, int idx, char prev) {
  string ret = to_string(idx) + "," + string(1, prev);
  for (int i : rem) {
    ret += "," + to_string(i);
  }
  return ret;
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
  string separator = grouping ? "," : "?";
  for (int i = 0; i < 5; ++i) {
    ret += inp;
    ret += separator;
  }
  ret.pop_back();
  return ret;
}

unordered_map<string, long long int> memo;

int r(vector<int> rem, string &seq, int idx, char prev) {
  string hsh = h(rem, idx, prev);

  if (memo.find(hsh) != memo.end()) {
    return memo[hsh];
  }

  if (idx < 0) {
    memo[hsh] = (rem.empty() || (!rem.empty() && rem[0] == 0)) ? 1 : 0;
    return memo[hsh];
  }

  char cur_c = seq[idx];
  int result = 0;

  switch (cur_c) {
    case '#': {
      if (!rem.empty() && rem.back() > 0) {
        rem[rem.size() - 1]--;
        result = r(rem, seq, idx - 1, '#');
        rem[rem.size() - 1]++;
      }
      result += r(rem, seq, idx - 1, '.');
      break;
    }
    case '.': {
      if (!rem.empty() && prev == '#' && rem.back() != 0) {
        break;
      }

      vector<int> remcpy = rem;
      result = r(rem, seq, idx - 1, '.');
      break;
    }
    default: {
      int sum = 0;
      vector<int> rem2 = rem;

      bool can_use_op = true;  // '.'
      if (prev == '#') {
        if (rem.empty() || rem.back() != 0) {
          can_use_op = false;
        }
      }

      if (!rem.empty() && rem.back() == 0) {
        rem.pop_back();
      }

      bool can_use_brk = !rem2.empty() && rem2.back() > 0;

      if (can_use_op) {
        string curhsh = h(rem, idx - 1, '.');
        sum += r(rem, seq, idx - 1, '.');
      }

      if (can_use_brk) {
        rem2[rem2.size() - 1]--;
        string curhsh = h(rem2, idx - 1, '#');
        sum += r(rem2, seq, idx - 1, '#');
      }

      result = sum;
      break;
    }
  }

  memo[hsh] = result;
  return result;
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
    res += r(ivals, layout, layout.size() - 1, '.');
  }
  cout << "res is " << res << endl;

  return 0;
}