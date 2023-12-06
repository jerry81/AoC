#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Mapping {
  long long int ss;  // unnecessary?
  long long int se;
  long long int ds;
  long long int de;
  long long int offset;  // from source to destination
  void print() {
    cout << "mapping " << endl;
    cout << "src start " << ss << "\n";
    cout << "dest start " << ds << "\n";
    cout << "src end " << se << "\n";
    cout << "dest end " << de << "\n";
    cout << "offset " << offset << "\n";
  }
};

void populateMap(ifstream& strm, unordered_map<long long int, Mapping>& outV) {
  string line;
  while (getline(strm, line)) {
    istringstream spaceStream(line);
    string tk;
    Mapping cur_m;
    vector<long long int> map_vals;
    while (spaceStream >> tk) {
      map_vals.push_back(stoll(tk));
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
  unordered_map<long long int, Mapping> seedRanges;
  unordered_map<long long int, Mapping>
      seedToSoilMap;  // int is start of source
  unordered_map<long long int, Mapping> soilToFertMap;
  unordered_map<long long int, Mapping> fertToWaterMap;
  unordered_map<long long int, Mapping> waterToLightMap;
  unordered_map<long long int, Mapping> lightToTempMap;
  unordered_map<long long int, Mapping> tempToHumidityMap;
  unordered_map<long long int, Mapping> humidityToLocationMap;

  string folder = "sminputs";
  ifstream seeds("./" + folder + "/seeds.txt");
  ifstream seedToSoil("./" + folder + "/seedToSoil.txt");
  ifstream soilToFert("./" + folder + "/soilToFert.txt");
  ifstream fertToWater("./" + folder + "/fertToWater.txt");
  ifstream waterToLight("./" + folder + "/waterToLight.txt");
  ifstream lightToTemp("./" + folder + "/lightToTemp.txt");
  ifstream tempToHumidity("./" + folder + "/tempToHumidity.txt");
  ifstream humidityToLocation("./" + folder + "/humidityToLocation.txt");


  string line;
  vector<long long int> preSeed;
  while (getline(seeds, line)) {
    istringstream spaceStream(line);
    string spaceToken;
    while (spaceStream >> spaceToken) {
      preSeed.push_back(stoll(spaceToken));
    }
  }

  for (int i = 0; i < preSeed.size(); i+=2) {
    long long int st = preSeed[i];
    long long int rng = preSeed[i+1];
    Mapping m;
    m.ss = st;
    m.se = st+rng;
    seedRanges[m.ss] = m;
  }

  populateMap(seedToSoil, seedToSoilMap);
  populateMap(soilToFert, soilToFertMap);
  populateMap(fertToWater, fertToWaterMap);
  populateMap(waterToLight, waterToLightMap);
  populateMap(lightToTemp, lightToTempMap);
  populateMap(tempToHumidity, tempToHumidityMap);
  populateMap(humidityToLocation, humidityToLocationMap);


  vector<unordered_map<long long int, Mapping>> maps = {
      seedToSoilMap,  soilToFertMap,     fertToWaterMap,       waterToLightMap,
      lightToTempMap, tempToHumidityMap, humidityToLocationMap};

  long long int lowest = LLONG_MAX;

  for (long long int seedItem : seedsv) {
    long long int src = seedItem;

    for (auto m : maps) {
      for (auto [startSrc, mapping] : m) {
        if (src >= startSrc && src < mapping.se) {
          // range found
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