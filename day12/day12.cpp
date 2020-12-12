
#include <complex>
#include <iostream>
#include <string>

using namespace std;

int main() {
    complex<int> pos_part1(0, 0);
    complex<int> pos_part2(0, 0);
    complex<int> ship_dir(1, 0);
    complex<int> waypoint(10, 1);
    string line_in;
    while (cin >> line_in) {
        char action = line_in[0];
        int value = stoi(line_in.substr(1));
        switch (action) {
            case 'N': {
                complex<int> dn(0, value);
                pos_part1 += dn;
                waypoint += dn;
                break;
            }
            case 'S': {
                complex<int> ds(0, -value);
                pos_part1 += ds;
                waypoint += ds;
                break;
            }
            case 'E':
                pos_part1 += value;
                waypoint += value;
                break;
            case 'W':
                pos_part1 -= value;
                waypoint -= value;
                break;
            case 'L': {
                complex<int> rl = pow(complex<double>(0, 1), value / 90);
                ship_dir *= rl;
                waypoint *= rl;
                break;
            }
            case 'R': {
                complex<int> rr = pow(complex<double>(0, -1), value / 90);
                ship_dir *= rr;
                waypoint *= rr;
                break;
            }
            case 'F':
                pos_part1 += ship_dir * value;
                pos_part2 += waypoint * value;
                break;
            default:
                cout << "Invalid action: " << action << endl;
        }
    }
    
    cout << "Part 1: " << abs(pos_part1.real()) + abs(pos_part1.imag()) << endl;
    cout << "Part 2: " << abs(pos_part2.real()) + abs(pos_part2.imag()) << endl;
    return 0;
}