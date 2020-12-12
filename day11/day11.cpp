
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class floor {
    public:
        vector<string> floor_rows;
    public:
        floor() : floor_rows{} {}

        void add_row(string row) {
            floor_rows.push_back('.' + row + '.');  // apply horizontal padding
        }

        void add_v_pad() {
            floor_rows.insert(floor_rows.begin(), string(floor_rows[0].size(), '.'));
            floor_rows.push_back(string(floor_rows[0].size(), '.'));
        }

        int count_neighbours(int r, int c) {
            int neighbours = 0;
            for (int i: {-1, 0, 1}) {
                for (int j: {-1, 0, 1}) {
                    if (j == 0 && i == 0)            { continue; }
                    if (floor_rows[r+i][c+j] == '#') { ++neighbours; }
                }
            }
            return neighbours;
        }

        int count_visable(int r, int c) {
            int visible = 0;
            int dist = 1;
            for (int i: {-1, 0, 1}) {
                for (int j: {-1, 0, 1}) {
                    if (j == 0 && i == 0) { continue; }
                    int dist = 1;
                    int _i = r + (i * dist);
                    int _j = c + (j * dist);
                    while (_i >= 0 && _i < floor_rows.size() && _j >= 0 && _j < floor_rows[0].size()) {
                        if (floor_rows[_i][_j] == '#') { 
                            ++visible; 
                            break;
                        } else if (floor_rows[_i][_j] == 'L') {
                            break;
                        }
                        ++dist;
                        _i = r + (i * dist);
                        _j = c + (j * dist);
                    }
                }
            }
            return visible;
        }

        bool apply_update(bool part2 = false) {
            vector<int> r_change{};
            vector<int> c_change{};
            for (int r = 1; r < floor_rows.size() - 1; ++r) {
                for (int c = 1; c < floor_rows[0].size(); ++c) {
                    char p = floor_rows[r][c];
                    if (p != '.') {
                        int ns = part2 ? count_visable(r, c) : count_neighbours(r, c);
                        if ((p == '#' && ns > (part2 ? 4 : 3)) || (p == 'L' && ns == 0)) {
                            r_change.push_back(r);
                            c_change.push_back(c);
                        }
                    }
                    
                }
            }

            for (int i = 0; i < r_change.size(); ++i) {
                floor_rows[r_change[i]][c_change[i]] = floor_rows[r_change[i]][c_change[i]] == '#' ? 'L' : '#';
            }
            return !r_change.empty();
        }

        int occupied_seats() {
            int occupied = 0;
            for (int r = 1; r < floor_rows.size() - 1; ++r) {
                for (int c = 1; c < floor_rows[0].size(); ++c) {
                    if (floor_rows[r][c] == '#') { ++occupied; }
                }
            }
            return occupied;
        }
};


ostream& operator<<(ostream& os, const floor& __f) {
    for (int i = 0; i < __f.floor_rows.size(); ++i) {
        cout << __f.floor_rows[i] << endl;
    }
    cout << endl;
    return cout;
}

int main() {
    floor waiting_room;
    floor waiting_room_copy;
    string line_in;
    while (cin >> line_in) {
        waiting_room.add_row(line_in);
        waiting_room_copy.add_row(line_in);
    }
    waiting_room.add_v_pad();
    waiting_room_copy.add_v_pad();

    while (waiting_room.apply_update());
    while (waiting_room_copy.apply_update(true));

    cout << "Part 1: " << waiting_room.occupied_seats() << endl;
    cout << "Part 2: " << waiting_room_copy.occupied_seats() << endl;
    return 0;
}
