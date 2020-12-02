
#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main() {
    string line_in;
    auto const pattern = regex("(\\d+)-(\\d+) ([a-z]): ([a-z]*)"); 

    int part1_valid_passwords = 0;
    int part2_valid_passwords = 0;
    while (getline(cin, line_in)) {
        // Parsing
        smatch match_results = smatch{};
        regex_match(line_in, match_results, pattern);
        // Conversion
        int min = stoi(match_results[1]);
        int max = stoi(match_results[2]);
        char required = match_results[3].str()[0];
        string password = match_results[4].str();

        // Part 1
        int count = 0;
        for (char c : password) {
            if (c == required) {
                ++count;
            }
        }
        if (min <= count && count <=max) {
            ++part1_valid_passwords;
        }

        // Part 2
        --min;
        --max;
        if ((password[min] == required || password[max] == required) && password[min] != password[max]) {
            ++part2_valid_passwords;
        }
    }

    cout << "Part 1: " << part1_valid_passwords << endl;
    cout << "Part 2: " << part2_valid_passwords << endl;
    return 0;
}