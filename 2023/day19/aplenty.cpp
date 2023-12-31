#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const string FNAME = "input.txt";

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

bool run(vector<int> props, string k) {
  vector<string> wf = workflows[k];
  for (string s : wf) {
    if (s.find(':') != string::npos) {
      // cause effect case
      vector<string> spl_res = split_by(s, ':');
      string left = spl_res[0];
      char comparator = left.find('>') != string::npos ? '>' : '<';
      vector<string> spl_left = split_by(left, comparator);
      int propidx = PROP_MAPPING[spl_left[0]];
      int compared_val = stoi(spl_left[1]);
      bool check = props[propidx] > compared_val;
      if (comparator == '<') check = !check;

      string right = spl_res[1];
      if (!check) continue;

      s = right;
    }

    if (s == "A") return true;

    if (s == "R") return false;

    // it's another key
    return run(props, s);
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
  ++i;
  for (int j = i; j < all_lines.size(); ++j) {
    string str = all_lines[j];
    string trimmed = str.substr(1, str.size() - 2);
    vector<string> tokens = split_by(trimmed, ',');
    vector<int> itokens;
    for (string token : tokens) {
      vector<string> spltokens = split_by(token, '=');
      itokens.push_back(stoi(spltokens[1]));
    }
    props.push_back(itokens);
  }
  long long int res = 0;

  for (vector<int> v : props) {
    long long int sum = 0;
    for (int i : v) sum += i;

    if (run(v, "in")) {
      cout << "SUCCESS" << endl;
      res += sum;
    }
    // go through workflow - if pass then add to res
  }
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