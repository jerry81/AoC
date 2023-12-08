#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

const string FNAME = "input.txt";
unordered_map<char, int> FACE = {
  {'A', 14}, {'K', 13}, {'Q', 12}, {'J', 11}, {'T', 10}
};
struct Hand {
  int score;
  vector<int> items;
  Hand(string s, string sc) {
    for (char c: s) {
      if (isdigit(c)) {
        items.push_back(c - '0');
      } else {
        items.push_back(FACE[c]);
      }
    }
    score = stoi(sc);
  }
  void print() {
    cout << "items are " << endl;
    for (int i: items) {
      cout << i << endl;
    }
    cout << "score is " << score << endl;
  }
};

int main() {
  // read from input
  ifstream strm(FNAME);
  string line;
  while (getline(strm, line)) {
    istringstream spaceStream(line);
    string spaceToken;
    vector<string> tkns;
    while (spaceStream >> spaceToken) {
      tkns.push_back(spaceToken);
    }
    Hand h = Hand(tkns[0], tkns[1]);
    h.print();
  }
  return 0;
}