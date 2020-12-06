
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * Function to reduce a vector of strings using some set combination mehtod such as std::set_union
 *   func signature: func(iterator1.begin(), iterator1.end(), iterator2.begin() iterator2.end(), backinserter)
 */
template<typename function>
string set_reduction(vector<string> all_strings, function func) {
    string string_total_reduction = all_strings[0];
    vector<char> vec_curr_reduction;
    for (int i = 1; i < all_strings.size(); ++i) {
        func(
            string_total_reduction.begin(), string_total_reduction.end(),
            all_strings[i].begin(), all_strings[i].end(),
            back_inserter(vec_curr_reduction)
        );
        string_total_reduction = string(vec_curr_reduction.data(), vec_curr_reduction.size());
        vec_curr_reduction = vector<char>{};
    }
    return string_total_reduction;
}

int main() {
    string line_in;
    vector<vector<string>> answers_from_groups;
    vector<string> group_answers{};
    while(getline(cin, line_in)) {
        if (line_in.length() == 0) {
            answers_from_groups.push_back(group_answers);
            group_answers = vector<string>{};
        } else {
            sort(line_in.begin(), line_in.end());
            group_answers.push_back(line_in);
        }
    }
    answers_from_groups.push_back(group_answers);

    int part1_num_yes = 0;
    int part2_num_unique_yes = 0;
    for (vector<string> group_answers : answers_from_groups) {
        part1_num_yes += set_reduction(
            group_answers, 
            set_union<string::iterator, string::iterator, back_insert_iterator<vector<char>>>
        ).length();
        part2_num_unique_yes += set_reduction(
            group_answers, 
            set_intersection<string::iterator, string::iterator, back_insert_iterator<vector<char>>>
        ).length();
    }

    cout << "Part 1: " << part1_num_yes << endl;
    cout << "Part 2: " << part2_num_unique_yes << endl;
    return 0;
}