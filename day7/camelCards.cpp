#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

const string FNAME = "input.txt";
// types
// FIVE 6
// FOUR 5
// FH 4
// THREE 3
// TP 2
// ONE 1
// H 0
unordered_map<char, int> FACE = {
  {'A', 14}, {'K', 13}, {'Q', 12}, {'J', 11}, {'T', 10}
};
struct Hand {
  int score;
  string orig;
  vector<int> items;
  int rnk = 0;
  int mx = INT_MIN;
  Hand(string s, string sc) {
    orig = s;
    unordered_map<int, int> freq;
    for (char c: s) {
      int item = isdigit(c) ? c - '0' : FACE[c];
      items.push_back(item);
      freq[item]++;
      mx = max(mx, item);
    }
    bool triple = false;
    bool quint = false;
    bool quad = false;
    bool pair = false;
    bool twopair = false;
    bool fullhouse = false;

    for (auto [k,v]: freq) {
      if (v == 5) quint = true;
      if (v == 4) quad = true;
      if (v == 3) {
        triple = true;
      }
      if (v == 2) {
        if (pair == true) twopair = true;
        pair = true;
      }
    }
    if (quint) {
      rnk = 6;
    } else if (quad) {
      rnk = 5;
    } else if (pair && triple) {
      rnk = 4;
    } else if (triple) {
      rnk = 3;
    } else if (twopair) {
      rnk = 2;
    } else if (pair) {
      rnk = 1;
    }
    score = stoi(sc);
  }
  void print() {
    cout << "items are " << endl;
    for (int i: items) {
      cout << i << endl;
    }
    cout << "rank is " << rnk << endl;
    cout << "score is " << score << endl;
  }
};

bool compare_hands(const Hand a, const Hand b) {
  if (a.rnk != b.rnk) {
    return a.rnk < b.rnk;
  } else {
    if (a.rnk == 0) {
      if (a.mx != b.mx) {
        // return a.mx < b.mx;
      }
    }
    vector<int> ai = a.items;
    vector<int> bi = b.items;
    for (int i = 0; i < ai.size(); ++i) {
      int ca = ai[i];
      int cb = bi[i];
      if (ca != cb) return ca < cb;
    }
    return false;
  }
}

int main() {
  // read from input
  ifstream strm(FNAME);
  string line;
  vector<Hand> hands;
  while (getline(strm, line)) {
    istringstream spaceStream(line);
    string spaceToken;
    vector<string> tkns;
    while (spaceStream >> spaceToken) {
      tkns.push_back(spaceToken);
    }
    Hand h = Hand(tkns[0], tkns[1]);
    hands.push_back(h);
  }
  sort(hands.begin(), hands.end(), compare_hands);
  long long int multi = 1;
  long long int res = 0;
  for (auto h: hands) {
    cout << h.orig << ": " << h.rnk << ", high card " << h.mx << endl;
    cout << "adding " << multi << " times " << h.score << endl;
    long long int toAdd = (multi * (long long int)h.score);
    // cout << "toAdd " << toAdd << endl;
    res += toAdd;
    cout << "res is currently " << res << endl;
   //  h.print();
    multi++;
    // cout << "multi is " << multi << endl;
  }
  cout << res << endl;
  return 0;
}