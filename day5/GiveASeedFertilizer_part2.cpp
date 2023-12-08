#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
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

void populateMap(ifstream& strm, map<long long int, Mapping>& outV) {
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
    outV[cur_m.ds] = cur_m;
  }
}

map<long long int, Mapping> mergeMaps(map<long long int, Mapping> dest, map<long long int, Mapping> src) {
  map<long long int, Mapping> merged;
  // example dest is humidity-to-location, src is temperature to humidity
  /* dest
    ds 56
    de 60
    ss 93
    se 97
    offset -37

    ds 60
    de 97
    ss 56
    se 93
    offset 4

    SRC
    ds 0
    de 1
    ss 69
    se 70
    offset -69

    ds 1
    de 70
    ss 0
    se 69
    offset 1

    MERGED
    ds 0
    de 1
    ss 69
    se 70
    offset -69

    ds 1
    de 56
    ss 0
    se 55
    offset -54
  */

   for (auto [k,v]:dest) {
     v.print();
   };

   for (auto [k,v]:src) {
     v.print();
   };
   return dest;
}

int main() {
  map<long long int, Mapping> seedRanges;
  map<long long int, Mapping>
      seedToSoilMap;  // int is start of source
  map<long long int, Mapping> soilToFertMap;
  map<long long int, Mapping> fertToWaterMap;
  map<long long int, Mapping> waterToLightMap;
  map<long long int, Mapping> lightToTempMap;
  map<long long int, Mapping> tempToHumidityMap;
  map<long long int, Mapping> humidityToLocationMap;

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


  vector<map<long long int, Mapping>> maps = {
      seedToSoilMap,  soilToFertMap,     fertToWaterMap,       waterToLightMap,
      lightToTempMap, tempToHumidityMap, humidityToLocationMap};


  mergeMaps(tempToHumidityMap, humidityToLocationMap);
  long long int lowest = LLONG_MAX;

  cout << "lowest is " << lowest << endl;
  return 0;
}