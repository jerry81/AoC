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

vector<string> split_by_str(string s, string delim) {
  size_t pos = 0;
  string token1;  // define a string variable
  vector<string> res;
  while ((pos = s.find(delim)) != std::string::npos) {
    token1 = s.substr(0, pos);  // store the substring
    res.push_back(token1);
    s.erase(0, pos + delim.length()); /* erase() function store the current
                                         positon and move to next token. */
  }
  res.push_back(s);
  return res;
}

struct Signal {
  char type;
  vector<string> outputs;
  void print() {
    cout << "type is " << type << endl;
    cout << "outputs " << endl;
    for (string s : outputs) cout << s << endl;
  }
};

int main() {
  vector<string> signals = read_lines_into_vec();
  unordered_map<string, Signal*> signals_map;
  for (string s : signals) {
    vector<string> tokens = split_by_str(s, " -> ");
    Signal* sig = new Signal();

    sig->type = tokens[0][0];

    sig->outputs = split_by_str(tokens[1], ", ");
    string trimmed = tokens[0].substr(1);
    signals_map[trimmed] = sig;
  }
  return 0;
}