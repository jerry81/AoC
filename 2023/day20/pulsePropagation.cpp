#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const string FNAME = "sm.txt";

vector<string> read_lines_into_vec() {
  ifstream strm(FNAME);
  string line;
  vector<string> lines;
  while (getline(strm, line)) {
    lines.push_back(line);
  }
  return lines;
}

vector<string> split_by_str(string s, string delim) {
  size_t pos = 0;
  string token1;  // define a string variable
  vector<string> res;
  while ((pos = s.find(delim)) != std::string::npos) {
    token1 = s.substr(0, pos);  // store the substring
    res.push_back(token1);
    s.erase(0, pos + delim.length()); /* erase() function store the current
                                         positon and move to next token. */
  }
  res.push_back(s);
  return res;
}

struct Signal {
  char type;
  vector<string> outputs;
  bool state = false;  // low
  unordered_map<string, bool> last_inputs;
  int high_input_count = 0;
  int input_count = 0;
  bool all_on() { return high_input_count == input_count; }
  tuple<queue<pair<string, bool>>, int, int> process(bool input,
                                                     string signal_name) {
    tuple<queue<pair<string, bool>>, int, int> ret;
    int lows = 0;
    int highs = 0;
    switch (type) {
      case 'b': {
        for (string s : outputs) {
          get<0>(ret).push({s, false});
          lows++;
        }
        break;
      }
      case '&': {
        if (input) {
          if (last_inputs.find(signal_name) == last_inputs.end()) {
            last_inputs[signal_name] = true;
            high_input_count++;
            input_count++;
          } else if (!last_inputs[signal_name]) {
            high_input_count++;
            last_inputs[signal_name] = true;
          }
        } else {
          if (last_inputs.find(signal_name) == last_inputs.end()) {
            last_inputs[signal_name] = false;
            input_count++;
          } else if (last_inputs[signal_name]) {
            high_input_count--;
            last_inputs[signal_name] = false;
          }
        }
        bool output_signal = !all_on();
        for (string s : outputs) {
          get<0>(ret).push({s, output_signal});
          if (output_signal) {
            highs++;
          } else {
            lows++;
          }
        }
        break;
      }
      case '%': {
        if (!input) {
          state = !state;
          for (string s : outputs) {
            get<0>(ret).push({s, state});
            if (state) {
              highs++;
            } else {
              lows++;
            }
          }
        }
        break;
      }
      default: {
        // no-op
      }
    }
    get<1>(ret) = lows;
    get<2>(ret) = highs;
    return ret;
  }
  void print() {
    cout << "type is " << type << endl;
    cout << "outputs " << endl;
    for (string s : outputs) cout << s << endl;
  }
};

int main() {
  queue<string> q;
  vector<string> signals = read_lines_into_vec();
  unordered_map<string, Signal*> signals_map;
  for (string s : signals) {
    vector<string> tokens = split_by_str(s, " -> ");
    Signal* sig = new Signal();

    sig->type = tokens[0][0];

    sig->outputs = split_by_str(tokens[1], ", ");
    string trimmed = tokens[0].substr(1);
    signals_map[trimmed] = sig;
  }
  int low = 0;
  int high = 0;

  for (int i = 0; i < 1000; ++i) {
    queue<pair<string, bool>> q;
    q.push({"roadcaster", false});
    low+=1;
    while (!q.empty()) {
      queue<pair<string, bool>> nq;
    //  cout << "q has " << endl;
      // auto copy = q;
      // while (!copy.empty()) {
      //   cout << copy.front().first << endl;;
      //   copy.pop();
      // }
      while (!q.empty()) {
        pair<string, bool> cur = q.front();
        q.pop();
        Signal* cur_s = signals_map[cur.first];
        auto [q2, l, h] = cur_s->process(cur.second, cur.first);
        cout << cur.first << " returns " << l << "," << h << endl;
        low += l;
        high += h;
        while (!q2.empty()) {
          nq.push(q2.front());
          q2.pop();
        }
      }
      q = nq;
    }
  }
  cout << "low is " << low << endl;
  cout << "high is " << high << endl;
  return 0;
}