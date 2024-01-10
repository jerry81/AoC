#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

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
    s.erase(0, pos + delim.length()); /* erase() function store the current                                positon and move to next token. */
  }
  res.push_back(s);
  return res;
}

int main() {
  // brute force: create disjoint set omitting 012 013 014... 2^n possibilities
  unordered_map<string, unordered_set<string>> e;
  vector<string> lines = read_lines_into_vec();
  for (string s: lines) {
    vector<string> tokens = split_by_str(s,": ");
    string parent = tokens[0];
    vector<string> neighbors = split_by_str(tokens[1], " ");
    for (string n: neighbors) {
      e[parent].insert(n);
      e[n].insert(parent);
    }
  }
  for (auto [k,st]: e) {
    cout << k << " has neighbors " <<endl;
    for (string s: st) cout << s << endl;
  }
  return 0;
}

/*

jqt: 4 <-
rhn: 4
xhk: 5
nvd: 5 <-
rsh: 4
frs: 4
pzl: 4 <-
lsr: 5
hfx: 5 <-
cmg: 5 <-
qnr: 4
lhk: 4
bvb: 5 <-
ntq: 4
rzs: 4

doesn't seem to have anything to do with connection count.

jqt: rhn xhk nvd
rsh: frs pzl lsr
xhk: hfx
cmg: qnr nvd lhk bvb
rhn: xhk bvb hfx
bvb: xhk hfx
pzl: lsr hfx nvd
qnr: nvd
ntq: jqt hfx bvb xhk
nvd: lhk
lsr: lhk
rzs: qnr cmg lsr rsh
frs: qnr lhk lsr

exactly 3 wires to cut that make 2 disjoint sets.

TIL: this is called global minimum cut algorithm
classic problem
- network design, social network, etc
- karger is popular
  - randomized algo
  - repeatedly "contract" random edges until only 2 nodes
    - contract means to merge two nodes into one node
    - all the edges leading to both nodes are reconnected to a single node
    - edges between the two nodes are removed altogether
    - last edges standing when there are only 2 nodes left are the min cut
*/