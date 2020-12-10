
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<int> adapters{0};
    string line_in; 
    while (cin >> line_in) {
        adapters.push_back(stoi(line_in));
    }
    sort(adapters.begin(), adapters.end());

    // Part 1
    int one_j_diffs = 0;
    int three_j_diffs = 1;  // start at 1 as built-in adapter always 3 more than highest
    map<int, long> adapter_inputs{};
    adapter_inputs.insert(pair<int, long>(0, 1));
    for (int i = 0; i < adapters.size() - 1; ++i) {
        switch (adapters[i+1] - adapters[i]) {
        case 1:
            ++one_j_diffs;
            break;
        case 3:
            ++three_j_diffs;
            break;
        default: break;
        }
        long curr_inputs = adapter_inputs.find(adapters[i])->second;
        for (int j = 1; j <= 3; ++j) {
            auto it = adapter_inputs.find(adapters[i] + j);
            if (it != adapter_inputs.end()) {
                it->second += curr_inputs;
            } else {
                adapter_inputs.insert(pair<int, long>(adapters[i] + j, curr_inputs));
            }
        }
    }

    cout << "Part 1: " << one_j_diffs * three_j_diffs << endl;
    cout << "Part 2: " << adapter_inputs.find(adapters[adapters.size() - 1])->second << endl;
    return 0;
}