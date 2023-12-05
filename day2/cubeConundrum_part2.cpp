#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    std::ifstream inputFile("processed.txt"); // Replace "your_input_file.txt" with the actual file name

    std::string line;
    long long int res = 0;
    // Read the file line by line and write to the output file

    // 12 red, 13 green, 14 blue
    while (std::getline(inputFile, line)) {
       int r = 0;
       int b = 0;
       int g = 0;
        vector<string> tokens;
        istringstream semicolonStream(line);
        string curtoken;
        while (getline(semicolonStream, curtoken, ';')) {
          tokens.push_back(curtoken);
        }

        vector<vector<string>> newTokens;
        for (const string tk: tokens) {
          istringstream spaceStream(tk);
          string spaceToken;
          vector<string> tempTokens;
          while (spaceStream >> spaceToken) {
            tempTokens.push_back(spaceToken);
          }
          newTokens.push_back(tempTokens);
        }
        for (vector<string> game: newTokens) {
          int quantity = 0;

          for (string tok: game) {
            if (tok == "blue" || tok == "blue,") {
              b = max(b, quantity);
            } else if (tok == "green," || tok == "green") {
              g = max(g, quantity);
            } else if (tok == "red" || tok == "red,") {
              r = max(r,quantity);
            } else {
              quantity = stoi(tok);
            }
          }
        }
        long long int pwr = r*g*b;
        res+=pwr;
    }

    // Close the files after reading and writing
    inputFile.close();

    std::cout << res << endl; // Return success
}
