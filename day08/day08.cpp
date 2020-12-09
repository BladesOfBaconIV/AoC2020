
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

pair<bool, int> run_instrs(vector<pair<string, int>> boot_instructions, bool changes_left, vector<int> seen_ptrs, int curr_ptr = 0, int curr_acc = 0, int depth = 0) {
    vector<int> seen_ptrs_copy;
    copy(seen_ptrs.begin(), seen_ptrs.end(), back_inserter(seen_ptrs_copy));
    while (find(seen_ptrs_copy.begin(), seen_ptrs_copy.end(), curr_ptr) == seen_ptrs_copy.end() && curr_ptr != boot_instructions.size()) {
        seen_ptrs_copy.push_back(curr_ptr);
        pair<string, int> command = boot_instructions[curr_ptr];
        if (command.first == "acc") { 
            curr_acc += command.second; 
        } else if (command.first == "jmp") { 
            if (changes_left) {
                pair<bool, int> result = run_instrs(boot_instructions, false, seen_ptrs_copy, curr_ptr + 1, curr_acc, depth + 1);
                if (result.first) {
                    return result;
                }
            }
            curr_ptr += command.second;
            continue;
        } else if (command.first == "nop" && changes_left) { 
            pair<bool, int> result = run_instrs(boot_instructions, false, seen_ptrs_copy, curr_ptr + command.second, curr_acc, depth + 1);
            if (result.first) {
                return result;
            }
        }
        ++curr_ptr;
    }
    return pair<bool, int>((curr_ptr == boot_instructions.size()), curr_acc);
}

int main() {
    vector<pair<string, int>> boot_instructions{};
    string line_in;
    while (getline(cin, line_in)) {
        string instr = line_in.substr(0, 3);
        int arg = stoi(line_in.substr(3));
        boot_instructions.push_back(pair<string, int>(instr, arg));
    }

    vector<int> seen_instr{};
    cout << "Part 1: " << run_instrs(boot_instructions, false, seen_instr).second << endl;
    pair<bool, int> part2 = run_instrs(boot_instructions, true, seen_instr);
    if (!part2.first) {
        cout << "Failed to terminate correctly" << endl;
    } else {
        cout << "Part 2: " << part2.second << endl;
    }
    return 0;
}
