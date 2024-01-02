#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const string FNAME = "input.txt";

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
  bool is_default() {
    bool ret = true;
    switch (type) {
      case '%': {
        return state == false;
      }
      case '&': {
        return high_input_count == 0;
      }
      default: {
      }
    }
    return ret;
  }
  bool all_on() { return high_input_count == input_count; }

  tuple<queue<tuple<string, bool, string>>, int, int, bool> process(
      bool input, string signal_name, string previous,
      unordered_map<string, Signal*>& sig_map) {
    tuple<queue<tuple<string, bool, string>>, int, int, bool> ret;
    int lows = 0;
    int highs = 0;
    switch (type) {
      case 'b': {
        for (string s : outputs) {
          get<0>(ret).push({s, false, signal_name});
          lows++;
        }
        break;
      }
      case '&': {
        if (input) {
          if (last_inputs.find(previous) == last_inputs.end()) {
            last_inputs[previous] = true;
            high_input_count++;
          } else if (!last_inputs[previous]) {
            high_input_count++;
            last_inputs[previous] = true;
          }
        } else {
          if (last_inputs.find(previous) == last_inputs.end()) {
            last_inputs[previous] = false;
          } else if (last_inputs[previous]) {
            high_input_count--;
            last_inputs[previous] = false;
          }
        }
        sig_map[signal_name]->high_input_count = high_input_count;
        sig_map[signal_name]->last_inputs = last_inputs;

        bool output_signal = !all_on();
        for (string s : outputs) {
          get<0>(ret).push({s, output_signal, signal_name});
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
          sig_map[signal_name]->state = state;
          for (string s : outputs) {
            get<0>(ret).push({s, state, signal_name});
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
    get<3>(ret) = is_default();
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
  for (auto [k, v] : signals_map) {
    for (string s2 : v->outputs) {
      if (signals_map.find(s2) == signals_map.end()) continue;

      signals_map[s2]->input_count++;
    }
  }

  int low = 0;
  int high = 0;
  int divisor = 0;
  int count = 0;
  while (true) {
    count++;
    int low_count = 0;
    queue<tuple<string, bool, string>> q;
    q.push({"roadcaster", false, "button"});
    low += 1;

    while (!q.empty()) {
      queue<tuple<string, bool, string>> nq;
      //  cout << "q has " << endl;
      // auto copy = q;
      // while (!copy.empty()) {
      //   cout << copy.front().first << endl;;
      //   copy.pop();
      // }

      while (!q.empty()) {
        tuple<string, bool, string> cur = q.front();
        q.pop();
        auto [current_signal, signal_value, previous_signal] = cur;
        if (signals_map.find(current_signal) == signals_map.end()) continue;
        Signal* cur_s = signals_map[current_signal];
        // cout << "currentsignal " << current_signal << endl;
        if (current_signal == "rx") cout << "hit " << endl;
                if (current_signal == "cx") cout << "hit cx " << signal_value << endl;

        if (!signal_value && current_signal == "rx") low_count++;
        auto [q2, l, h, is_d] = cur_s->process(signal_value, current_signal,
                                               previous_signal, signals_map);

        low += l;
        high += h;
        while (!q2.empty()) {
          nq.push(q2.front());
          q2.pop();
        }
      }

      q = nq;
    }
          // cout << "low_count is " << low_count << endl;

    if (low_count == 1) {
      cout << "count is " << count << endl;
      return 0;
    }
  }
  cout << "count is " << count << endl;
  cout << "low is " << low << endl;
  cout << "high is " << high << endl;
  // cout << "divisor is " << divisor << endl;
  // cout << "low total is " << low * (1000/divisor) << endl;
  // cout << "high total is " << high * (1000/divisor) << endl;
  return 0;
}