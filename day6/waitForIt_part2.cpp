#include <iostream>
#include <vector>
using namespace std;

using namespace std;

int main() {
  vector<pair<int, int>> td = {{55, 246}, {82, 1441}, {64, 1012}, {90, 1111}};
  long long int t = 55826490;
  long long int d = 246144110121111;
  long long int cnt = 0;
  long long int i = 1;
  long long int a;
  // binary search find upper bound
  while (i < t) {
    a = t - i;
    if (i * a > d) ++cnt;
    i++;
  }
  cout << cnt << endl;
}
