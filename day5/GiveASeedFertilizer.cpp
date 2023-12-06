#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>


using namespace std;

struct Mapping {
  int ss; // unnecessary?
  int se;
  int ds;
  int de;
  int offset; // from source to destination
  void print() {
    cout << "mapping " << endl;
    cout << "src start " << ss << "\n";
    cout << "dest start " << ds << "\n";
    cout << "src end " << se << "\n";
    cout << "dest end " << de << "\n";
    cout << "offset " << offset << "\n";
  }
};

int main() {
  unordered_map<int, Mapping> seedToSoilMap; // int is start of source
  ifstream seeds("./sminputs/seeds.txt");
  ifstream seedToSoil("./sminputs/seedToSoil.txt");
  string line;
  long long int res = 0;
  vector<int> seedsv;
  while (getline(seeds, line)) {
    istringstream spaceStream(line);
    string spaceToken;
    while (spaceStream >> spaceToken) {
      seedsv.push_back(stoi(spaceToken));
    }
  }

  while (getline(seedToSoil, line)) {
    istringstream spaceStream(line);
    string tk;
    Mapping cur_m;
    vector<int> map_vals;
    while (spaceStream >> tk) {
      map_vals.push_back(stoi(tk));
    }
    cur_m.ds = map_vals[0];
    cur_m.ss = map_vals[1];
    cur_m.offset = cur_m.ds - cur_m.ss;
    cur_m.de = cur_m.ds + map_vals[2];
    cur_m.se = cur_m.ss + map_vals[2];
    seedToSoilMap[cur_m.ss] = cur_m;
  }

  for (auto [k,v] : seedToSoilMap) {
    cout << "printing source start " << k << endl;
    v.print();
  }

  return 0;
}