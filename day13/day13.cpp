
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;


int main() {
    string target_depart_str;
    cin >> target_depart_str;
    int target_depart = stoi(target_depart_str);
    string bus_ids_str;
    vector<string> bus_ids;
    cin >> bus_ids_str;
    string id = "";
    for (char c : bus_ids_str) {
        if (c == ',') {
            bus_ids.push_back(id);
            id = "";
        } else {
            id += c;
        }
    }
    bus_ids.push_back(id);
    
    // Part 1
    int closest_bus = 0;
    int shortest_wait_time = target_depart;
    for (string bus_id : bus_ids) {
        if (bus_id == "x") { continue; }
        int bus = stoi(bus_id);
        int wait_time = bus - (target_depart % bus);
        // cout << bus << ' ' << wait_time << ' ' << shortest_wait_time << endl;
        if (wait_time < shortest_wait_time) {
            closest_bus = bus;
            shortest_wait_time = wait_time;
        }
    }

    cout << "Part 1: " << shortest_wait_time * closest_bus << endl;
    cout << numeric_limits<long>::max() << endl;
    return 0;
}