
#include <iostream>
#include <string>
#include <vector>


using namespace std;

int count_collisions(vector<string> map, int dx, int dy, int curr_col = 0, int curr_row = 0, char tree = '#') {
    int collisions = 0;
    while (curr_row < map.size()) {
        if (map[curr_row][curr_col] == tree) {
            ++collisions;
        }
        curr_row += dy;
        curr_col += dx;
        curr_col %= map[0].length();
    }
    return collisions;
}

int main() {
    // Read input into matrix (map)
    vector<string> map;
    string row;
    while (cin >> row) {
        map.push_back(row);
    }
    // Part 1
    int part1_collisions = count_collisions(map, 3, 1);
    cout << "Part 1: " << part1_collisions << endl;
    // Part 2
    int part2_collisions = part1_collisions;
    for (int dx : {1, 5, 7}) {
        part2_collisions *= count_collisions(map, dx, 1);
    }
    part2_collisions *= count_collisions(map, 1, 2);
    cout << "Part 2: " << part2_collisions << endl;
    return 0;
}