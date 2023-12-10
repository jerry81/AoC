#include <vector>
#include <iostream>
using namespace std;

using namespace std;

int main() {
  vector<pair<int, int>> td = {{55, 246}, {82, 1441}, {64, 1012}, {90,1111}};
  vector<int> results;
  for (auto [t,d]: td) {
    int cnt = 0;
    cout << "t " << t << endl;
    cout << "d " << d << endl;
    // get number of winning combos
    // should be a math formula, right?
    // h is units held
    // speed is h
    // t = 7, h = 1
    // 7-1 = 6*h = d
    // t = 7, h = 2
    // 5*h = 10
    // 4*3 = 12
    // 3*4 = 12
    // 2*5 = 10
    // 1*6 = 6
    int i = 1;
    int a;
    while (i < t) {
      a = t - i;
      if (i * a > d) ++cnt;
      i++;
    }
    results.push_back(cnt);
  }
  int res = results[0];
  for (int i = 1; i < results.size(); ++i) res*=results[i];
  cout<< "res " << res << endl;
}