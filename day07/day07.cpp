
#include <iostream>
#include <regex>
#include <string>

#include "../utils/graph.h"

using namespace std;

const string TARGET_BAG = "shiny gold";

int main() {
    auto const pattern_src = regex("^(\\w+ \\w+) .*$");
    auto const pattern_contains = regex("(\\d+) (\\w+ \\w+)");
    graph<string> bag_dependencies{};
    string line_in;
    while(getline(cin, line_in)) {
        smatch scr_smatch = smatch{};
        smatch contains_smatch = smatch{};
        regex_match(line_in, scr_smatch, pattern_src);
        string src = scr_smatch[1];
        while (regex_search(line_in, contains_smatch, pattern_contains)) {
            int weight = stoi(contains_smatch[1]);
            string dest = contains_smatch[2];
            line_in = contains_smatch.suffix().str();
            bag_dependencies.add_edge(src, dest, weight);
        }
    }

    set<string> holds_target{};
    for (auto const& k_v : bag_dependencies.g) {
        bool path_exists = bag_dependencies.path_exists(k_v.first, TARGET_BAG);
        if (path_exists) {
            holds_target.insert(k_v.first);
        }
    }

    cout << "Part 1: " << holds_target.size() << endl;
    cout << "Part 2: " << bag_dependencies.contents(TARGET_BAG) << endl;
    return 0;
}

