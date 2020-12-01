
#include <iostream>
#include <set>
#include <tuple>

using namespace std;

const int PROBLEM_TARGET = 2020;

tuple<int, int> find2(set<int> nums, int target = PROBLEM_TARGET) {
    for (int n : nums) {
        if (nums.count(target - n) > 0) {
            return tuple<int, int> {n, target - n};
        }
    }
    return tuple<int, int> {0, 0};
}

tuple<int, int, int> find3(set<int> nums, int target = PROBLEM_TARGET) {
    for (int n : nums) {
        tuple<int, int> found_vals = find2(nums, target - n);
        if (get<0>(found_vals) != 0) {
            return tuple<int, int, int> {n, get<0>(found_vals), get<1>(found_vals)};
        }
    }
    return tuple<int, int, int> {0, 0, 0};
}

int main() {
    set<int> vals {};
    int val;
    while (cin) {
        cin >> val;
        vals.insert(val);
    }
    auto part1_vals = find2(vals);
    cout << get<0>(part1_vals) * get<1>(part1_vals) << '\n';
    auto part2_vals = find3(vals);
    cout << get<0>(part2_vals) * get<1>(part2_vals) * get<2>(part2_vals) << '\n';
    return 0;
}