#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
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
unordered_map<string, vector<string>> workflows;
unordered_map<string, int> PROP_MAPPING = {
    {"x", 0}, {"m", 1}, {"a", 2}, {"s", 3}};

long long res = 0;
void get_ranges(vector<string> instructions, int xmin, int xmax, int mmin,
                int mmax, int amin, int amax, int smin, int smax) {
  if (instructions.empty()) return;

  string cur = instructions.front();
  instructions.erase(instructions.begin());
  if (cur == "R") return;

  if (cur == "A") {
    res += (xmax - xmin) * (mmax - mmin) * (amax - amin) * (smax - smin);
    return;
  }
  if (cur.find(':') != string::npos) {
    // cause effect case
    vector<string> spl_res = split_by(cur, ':');
    string left = spl_res[0];
    char comparator = left.find('>') != string::npos ? '>' : '<';
    vector<string> spl_left = split_by(left, comparator);
    string s = spl_left[0];
    int compared_val = stoi(spl_left[1]);
    string right = spl_res[1];
    if (s == "x") { // this can get messy.  use vector instead for params

      // true case
      if (comparator == '>') {
        int newxmin = max(xmin, compared_val);
        int newxmax = min(xmax, compared_val);
        if (right == "A") {
            get_ranges({"A"}, newxmin, xmax,mmin,mmax,amin,amax,smin,smax);
        }
        if (right != "R") { //
            get_ranges(workflows[right], xmin, newxmax,mmin, mmax,amin,amax,smin,smax);
        }
      }
    } else if (s == "m") {
    } else if (s == "a") {
    } else {
    }

    // update range for true case - go to right
    // is right R or A
    // if not then it is a key
    // update range for false case continue on with instructions
  } else {
    // it's another key
    // return get_ranges(instructions, )
  }
}
return false;
}

int main() {
  vector<string> all_lines = read_lines_into_vec();
  vector<vector<int>> props;  // decompose further 0x1m2a3s

  string s = ".";
  int i = 0;
  while (true) {
    s = all_lines[i];
    if (s.empty()) break;

    int pos = s.find('{');
    string key = s.substr(0, pos);
    string remainder = s.substr(pos + 1, s.size() - 2 - pos);
    vector<string> rules = split_by(remainder, ',');
    workflows[key] = rules;
    ++i;
  }
  // we only need workflow rules
  // some kind of stack or recursion needed
  // go through each possible success path
  // update range of props at each step of the path
  //
  // the flow is in -> s < 1351 ? a < 2006 ? qkq: m > 2090 ? A : rfg: qqz
  cout << "res is " << res << endl;
  return 0;
}

// token breakdown for workflows
/*
  before { -> key
  between { and } -> rules
  rules -> split by ','
    a<2006:qkq
    m>2090:A (early break)
    rfg
*/

/*

just one path:
15350040384000
167409079868000
*/