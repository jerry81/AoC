#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const string FNAME = "sminput.txt";

int main() {
  long long int sum = 0;
  ifstream strm(FNAME);
  string line;

  while (getline(strm, line)) {
    vector<int> items;
    cout << "line is " << line << endl;
    istringstream spaceStream(line);
    string spaceToken;
    while (spaceStream >> spaceToken) {
      items.push_back(stoi(spaceToken));
    }
  }
  cout << "sum " << sm << endl;
  return 0;
}