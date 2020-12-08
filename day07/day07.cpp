
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <set>
#include <tuple>

using namespace std;

const string TARGET_BAG = "shiny gold";

template <class T>
class graph {
    public:
        map<T, set<pair<int, T>>> g;
    public:
        graph() : g{} {}
        
        void add_edge(T src, T dest, int weight = 1) {
            auto it = g.find(src);
            if (it == g.end()) {
                set<pair<int, T>> s{};
                s.insert(pair<int, T>(weight, dest));
                g.insert(pair<T, set<pair<int, T>>>(src, s));
            } else {
                it->second.insert(pair<int, T>(weight, dest));
            }
        }

        bool path_exists(T src, T dest, set<T> known_connected = set<string>()) {
            auto it = g.find(src);
            if (it == g.end()) {
                return false;
            } else {
                bool path = false;
                for (pair<int, T> edge : it->second) {
                    if (path || edge.second == dest || known_connected.find(edge.second) != known_connected.end()) {
                        known_connected.insert(src);
                        return true;
                    } else {
                        path = path_exists(edge.second, dest, known_connected);
                    }
                }
                if (path) {
                    known_connected.insert(src);
                }
                return path;
            }
        }

        int contents(T root) {
            int total_contained = 0;
            auto it = g.find(root);
            if (it != g.end()) {
                for (pair<int, T> holding : it->second) {
                    total_contained += holding.first;
                    total_contained += holding.first * contents(holding.second);
                }
            }
            return total_contained;
        }
};

template <class T>
ostream& operator<<(ostream& os, const graph<T>& __g) {
    cout << "{" << endl;
    for (pair<T, set<pair<int, T>>> p : __g.g) {
        cout << "    " << p.first << " : [";
        for (pair<int, T> v : p.second) {
            cout << v.second << " (" << v.first << "), ";
        }
        cout << "]," << endl;
    }
    cout << "}";
    return cout;
}

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

