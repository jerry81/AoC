#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Mapping {
  int ss;  // unnecessary?
  int se;
  int ds;
  int de;
  int offset;  // from source to destination
  void print() {
    cout << "mapping " << endl;
    cout << "src start " << ss << "\n";
    cout << "dest start " << ds << "\n";
    cout << "src end " << se << "\n";
    cout << "dest end " << de << "\n";
    cout << "offset " << offset << "\n";
  }
};

void populateMap(ifstream& strm, unordered_map<int, Mapping>& outV) {
  string line;
  while (getline(strm, line)) {
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
    outV[cur_m.ss] = cur_m;
  }
}

int main() {
  unordered_map<int, Mapping> seedToSoilMap;  // int is start of source
  unordered_map<int, Mapping> soilToFertMap;
  unordered_map<int, Mapping> fertToWaterMap;
  unordered_map<int, Mapping> waterToLightMap;
  unordered_map<int, Mapping> lightToTempMap;
  unordered_map<int, Mapping> tempToHumidityMap;
  unordered_map<int, Mapping> humidityToLocationMap;

  ifstream seeds("./sminputs/seeds.txt");
  ifstream seedToSoil("./sminputs/seedToSoil.txt");
  ifstream soilToFert("./sminputs/soilToFert.txt");
  ifstream fertToWater("./sminputs/fertToWater.txt");
  ifstream waterToLight("./sminputs/waterToLight.txt");
  ifstream lightToTemp("./sminputs/lightToTemp.txt");
  ifstream tempToHumidity("./sminputs/tempToHumidity.txt");
  ifstream humidityToLocation("./sminputs/humidityToLocation.txt");

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

  populateMap(seedToSoil, seedToSoilMap);
  populateMap(soilToFert, soilToFertMap);
  populateMap(fertToWater, fertToWaterMap);
  populateMap(waterToLight, waterToLightMap);
  populateMap(lightToTemp, lightToTempMap);
  populateMap(tempToHumidity, tempToHumidityMap);
  populateMap(humidityToLocation, humidityToLocationMap);

  // lowest location number
  int lowest = INT_MAX;

  // for (auto [k, v] : seedToSoilMap) {
  //   cout << "checking " << k << endl;
  //   v.print();
  // }

  for (int seedItem : seedsv) {
    int src = seedItem;
    bool found = false;
    vector<unordered_map<int, Mapping>> maps = {
        seedToSoilMap,        soilToFertMap,  fertToWaterMap,
        waterToLightMap,      lightToTempMap, tempToHumidityMap,
        humidityToLocationMap};
    for (auto m : maps) {
      for (auto [startSrc, mapping] : m) {
        if (src >= startSrc && src < mapping.se) {
          // range found
          found = true;
          src = src + mapping.offset;
          break;
        }
      }
    }
    lowest = min(lowest, src);
  }
  cout << "lowest is " << lowest << endl;
  return 0;
}