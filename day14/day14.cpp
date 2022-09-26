
#include <iostream>
#include <map>
#include <regex>
#include <string>

using namespace std;

const char X = 'X';
const char ONE = '1';
const char ZERO = '0';

int main() {
    const regex mask_pattern = regex("[10X]{36}");
    const regex memory_pattern = regex("mem\\[(\\d+)\\] = (\\d+)");
    map<int, long> memory;
    string line_in;
    long ones_mask;
    long zeros_mask;

    while (getline(cin, line_in)) {
        if (line_in[1] == 'a') {  // new mask
            smatch mask_smatch{};
            regex_search(line_in, mask_smatch, mask_pattern);
            string str_mask = mask_smatch[0].str();
            ones_mask = stoll(str_mask.replace(str_mask.begin(), str_mask.end(), 'X', '0'), 0, 2);
            zeros_mask = stoll(str_mask.replace(str_mask.begin(), str_mask.end(), 'X', '1'), 0, 2);
        } else {
            smatch mem_smatch{};
            regex_search(line_in, mem_smatch, memory_pattern);
            int addr = stoi(mem_smatch[1]);
            long val = stol(mem_smatch[2]);
            val &= zeros_mask;
            val |= ones_mask;
            memory.insert(pair<int, long>(addr, val));
        }
    }
    
    long total = 0;
    for (auto k_v : memory) {
        total += k_v.second;
    }

    cout << "Part 1: " << total << endl;
    return 0;
}