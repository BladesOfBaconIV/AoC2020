
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int decode_string(string s, char one, char zero) {
    int value = 0;
    for (int i = s.length() - 1; i >= 0; --i) {
        if (s[s.length() - 1 - i] == one) {
            value += 1 << i;
        }
    }
    return value;
}

int main() {
    vector<int> seat_ids;
    string line_in;
    while(cin >> line_in) {
        string row_string = line_in.substr(0, 7);
        string col_string = line_in.substr(7);
        int row = decode_string(row_string, 'B', 'F');
        int col = decode_string(col_string, 'R', 'L');
        int seat_id = row * 8 + col;
        seat_ids.push_back(seat_id);
    }
    sort(seat_ids.begin(), seat_ids.end());
    // Part 2
    int empty_seat = 0;
    for (int i = 0; i < seat_ids.size() - 1; ++i) {  // up to second last index
        if (seat_ids[i + 1] - seat_ids[i] == 2) {
            empty_seat = seat_ids[i] + 1;
            break;
        }
    }

    cout << "Part 1: " << seat_ids[seat_ids.size() - 1] << endl;
    cout << "Part 2: " << empty_seat << endl;
    return 0;
}