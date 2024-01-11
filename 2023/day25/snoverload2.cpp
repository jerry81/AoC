#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
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

int main() {
  unordered_map<string, unordered_set<string>> e;
  srand((unsigned)time(0));

  auto bfs = [&](const auto &edges, string from,
                 string
                     to) {  // automatically deduce type (lambda function) [&]
                            // capture clause (capture variables by reference )
    unordered_set<string> visited;
    queue<vector<string>> paths;
    visited.insert(from);
    paths.push({from});

    while (!paths.empty()) {
      auto path = move(
          paths.front());  // std library, move operation - ref to front
                           // element, provide access to it, treat as rvalue
      paths.pop();
      if (path.back() == to) return path;
      for (auto edge_to :
           edges.at(path.back())) {  // [] is not available for const
        if (visited.find(edge_to) != visited.end())
          continue;  // instead of find, but only c++ 20

        visited.insert(edge_to);
        auto next = path;
        next.push_back(edge_to);
        paths.push(move(
            next));  // move is an optimizer.  still not sure when to use it.
      }
    }
    return vector<string>({});
  };

  const auto connectivity = [&](auto &edges, string from, string to) {
    auto clone = edges;
    auto path = bfs(clone, from, to);
    int res = 0;
    while (!path.empty()) {
      res++;
      for (auto [edgea, edgeb] : path | pairwise) {
        clone[edgea].erase(edgeb);
        clone[edgeb].erase(edgea);
      }
      bfs(clone, from, to);
    }
    return res;
  };

  vector<string> lines = read_lines_into_vec();
  for (string s : lines) {
    vector<string> tokens = split_by_str(s, ": ");
    string parent = tokens[0];
    vector<string> neighbors = split_by_str(tokens[1], " ");
    for (string n : neighbors) {
      e[parent].insert(n);
      e[n].insert(parent);
    }
  }

  return 0;
}
