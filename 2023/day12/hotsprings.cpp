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

// could do dp if needed
int r(vector<int> rem, string &seq, int idx, char prev) {
  if (idx < 0) {

    int val= rem.empty() ? 1 : 0;
    return val;
  }
  char cur_c = seq[idx];
  if (rem.empty()) {
    if (cur_c == '#') return 0;
    return r({}, seq, idx-1, cur_c);
  }
  int crem = rem.back();
  if (crem == 0) {
    if (cur_c != '#') {
      rem.pop_back();
      return r(rem, seq, idx-1, '.');
    } else {
      return 0;
    }
  }

  if (cur_c == '#') {
    rem[rem.size() - 1]--;
    return r(rem, seq, idx-1, '#');
  } else if (cur_c == '.') {
    if (prev == '#') {
      if (crem != 0) {
        return 0;
      }
    }
    return r(rem, seq, idx-1, '.');
  } else { // ? case
    vector<int> rem2 = rem;
    rem2[rem2.size()-1]--;
    return r(rem, seq, idx-1, '.') + r(rem2,seq,idx-1,'#');
  }
  cout << "idx is " << idx << endl;
  cout << "prev is " << prev << endl;
  cout << "cur_c is " << cur_c << endl;
  cout << "funneled here " << endl;
  return 0;
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
    for (string s: splByComma) ivals.push_back(stoi(s));
    if (layout == "?###????????") {
      cout << "examining " << endl;
      int example = r(ivals, layout, layout.size()-1, ' ');
      cout << "out is " << example << endl;
    }
    res+= r(ivals, layout, layout.size()-1, ' ');
  }
  cout << "res is " << res << endl;
  // split lines
  return 0;
}