#include <fstream>
#include <iostream>
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

vector<string> trickle_up(vector<string> orig) {
  bool op_made = true;
  int h = orig.size();
  vector<string> ret = orig;
  while (op_made) {
    op_made = false;
    for (int i = 1; i < h; ++i) {
      string curLine = ret[i];
      string aboveLine = ret[i - 1];
      string newAbvLine = aboveLine;
      string newLine = curLine;
      for (int j = 0; j < curLine.size(); ++j) {
        if (aboveLine[j] == '.' && curLine[j] == 'O') {
          // cout << "swapping " << endl
          newLine[j] = '.';
          newAbvLine[j] = 'O';
          op_made = true;
        }
      }
      ret[i-1] = newAbvLine;
      ret[i] = newLine;
    }
  }
  return ret;
}

int main() {
  vector<string> lines = read_lines_into_vec();
  vector<string> transformed = trickle_up(lines);
  cout << "checking " << endl;
  for (string s : transformed) cout << s << endl;
}