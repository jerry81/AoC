#include <vector>

using namespace std;

const vector<pair<int,int>> DIRECTIONS = {{0,1}, {0,-1}, {1,0}, {-1,0}};

void usage(int y, int x) {
  for (auto [dy,dx]: DIRECTIONS) {
    int ny = y+dx;
    int nx = y+dx;
    // etc...
  }
}