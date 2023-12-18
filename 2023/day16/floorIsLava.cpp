#include <fstream>
#include <string>
#include <vector>
#include <iostream>

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

int main () {
  vector<string> lines = read_lines_into_vec();
  cout << "lines is " << endl;
  for (string s: lines) {
    cout << s << endl;
  }
  return 0;
}


/*

*/