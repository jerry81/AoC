#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <sstream>

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

int main () {
  vector<string> all_lines = read_lines_into_vec();
  vector<string> props;
  unordered_map<string, vector<string>> workflows;
  string s = ".";
  int i = 0;
  while (true) {
    s = all_lines[i];
    if (s.empty()) break;
    int pos = s.find('{');
    string key = s.substr(0, pos);
    string remainder = s.substr(pos+1,s.size()-2-pos);

    vector<string> rules = split_by(remainder, ',');
    workflows[key] = rules;
    ++i;
  }
  ++i;
  for (int j = i; j < all_lines.size(); ++j) {
    props.push_back(all_lines[j]);
  }
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