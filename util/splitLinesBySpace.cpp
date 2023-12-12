#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split_by_space(string s) {
  vector<string> newTokens;
  istringstream spaceStream(s);
  string spaceToken;
  while (spaceStream >> spaceToken) {
    newTokens.push_back(spaceToken);
  }
  return newTokens;
}
