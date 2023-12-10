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
    int gameNumber = 1;
    // Read the file line by line and write to the output file

    // 12 red, 13 green, 14 blue
    while (std::getline(inputFile, line)) {
        bool fail = false;
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
              if (quantity > 14) {
                fail = true;
                break;
              }
            } else if (tok == "green," || tok == "green") {
              if (quantity > 13) {
                fail = true;
                break;
              }
            } else if (tok == "red" || tok == "red,") {
              if (quantity > 12) {
                fail = true;
                break;
              }
            } else {
              quantity = stoi(tok);
            }
          }
          if (fail) break;
        }
        if (!fail) res+=gameNumber;

        gameNumber++;
    }

    // Close the files after reading and writing
    inputFile.close();

    std::cout << res << endl; // Return success
}
