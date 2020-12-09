
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

const int PREAMBLE = 25;

bool two_sum(long* target_ptr) {
    long target = *target_ptr;
    for (int i = PREAMBLE; i > 1; --i) {
        long n = *(target_ptr - i);
        if (n < target && find(target_ptr - i + 1, target_ptr, target-n) != target_ptr) {
            return true;
        }
    }
    return false;
}

tuple<long*, long*> n_sum_contiguous(long* nums_start, long* target_ptr) {
    long target = *target_ptr;
    for (long* left = nums_start; left < target_ptr; ++left) {
        long total = *left;
        for (long* right = left + 1; right < target_ptr; ++ right) {
            total += *right;
            if (total == target) {
                return tuple<long*, long*>(left, right);
            } else if (total > target) {
                break;
            }
        }
    }
    return tuple<long*, long*>(nums_start, nums_start);
}

int main() {
    vector<long> nums{};
    string line_in;
    while (cin >> line_in) {
        nums.push_back(stol(line_in));
    }

    long* code_num_ptr = &nums[PREAMBLE];
    while (two_sum(code_num_ptr) && code_num_ptr < nums.data() + nums.size()) {
        ++code_num_ptr;
    }

    tuple<long*, long*> n_sum_range = n_sum_contiguous(nums.data(), code_num_ptr);
    long part2 = *min_element(get<0>(n_sum_range), get<1>(n_sum_range)) 
                    + *max_element(get<0>(n_sum_range), get<1>(n_sum_range));
    cout << "Part 1: " << *code_num_ptr << endl;
    cout << "Part 2: " << part2 << endl;
    return 0;
}