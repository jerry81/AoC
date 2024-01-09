#include <fstream>
#include <string>
#include <vector>

using namespace std;

const string FNAME = "sm.txt";

struct Hail {
  tuple<int, int, int> pos;
  tuple<int, int, int> vel;
};

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
  return res;
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

int main() {
  vector<string> inp = read_lines_into_vec();
  vector<Hail> hails;
  for (string s : inp) {
    vector<string> tokens = split_by_str(s, " @ ");
    string t1 = tokens[0];
    string t2 = tokens[1];
    Hail h;
    vector<string> t1s = split_by_str(t1, ", ");
    vector<string> t2s = split_by_str(t2, ", ");
    h.pos = {stoi(t1s[0]), stoi(t1s[1]), stoi(t1s[2])};
    h.vel = {stoi(t2s[0]), stoi(t2s[1]), stoi(t2s[2])};
  }
  return 0;
}