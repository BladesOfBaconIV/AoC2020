
/*
 *  Note for this problem the input was modified to reduce the complexity of the code
 *  replace all the blank lines in the input with a single '#' character (in vim run :%s/^$/#/g)
 */


#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

const set<string> EYE_CLRS{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

bool between(string n, int low, int high) {
    int n_int = stoi(n);
    return low <= n_int && n_int <= high;
}

bool valid_height(string h) {
    string units = h.substr(h.length() - 2);
    string value = h.substr(0, h.length() - 2);
    return (units == "cm" && between(value, 150, 193)) || (units == "in" && between(value, 59, 76));
}

bool valid_hair(string hc) {
    bool valid_hc = hc[0] == '#';
    for (char c: hc.substr(1)) {
        valid_hc = valid_hc && isalnum(c);
    }
    return valid_hc;
}

class passport {
    public:
        string birth_year, issue_year, expiration_year, height, 
                hair_colour, eye_colour, passport_id, country_id;
    public:
        passport(string byr = "", string iyr = "", string eyr = "", string hgt = "", 
                 string hcl = "", string ecl = "", string pid = "", string cid = "") {
            birth_year = byr;
            issue_year = iyr;
            expiration_year = eyr;
            height = hgt;
            hair_colour = hcl;
            eye_colour = ecl;
            passport_id = pid;
            country_id = cid;
        }

        void add_info(string info) {
            string info_type = info.substr(0, 3);
            string info_val = info.substr(4);
            if (info_type == "byr") { 
                birth_year = info_val; 
            } 
            else if (info_type == "iyr") { 
                issue_year = info_val; 
            } 
            else if (info_type == "eyr") { 
                expiration_year = info_val; 
            } 
            else if (info_type == "hgt") { 
                height = info_val; 
            } 
            else if (info_type == "hcl") { 
                hair_colour = info_val; 
            } 
            else if (info_type == "ecl") { 
                eye_colour = info_val; 
            } 
            else if (info_type == "pid") { 
                passport_id = info_val;
            } 
            else if (info_type == "cid") { 
                country_id = info_val;
            } 
            else { cout << "Unkown info_type: " << info_type << " with value " << info_val << endl; }
        }

        bool is_valid() {
            return birth_year.length() * issue_year.length() * expiration_year.length()
                * height.length() * hair_colour.length() * eye_colour.length() * passport_id.length() != 0;
        }
};

int main() {
    string line_in;
    vector<passport> passports;
    // Part 1
    passport current_passport{};
    int part1_valid_passports = 0;
    while(cin >> line_in) {
        if (line_in == "#") {
            part1_valid_passports += current_passport.is_valid();
            passports.push_back(current_passport);
            current_passport = passport{};
            continue;
        }
        current_passport.add_info(line_in);
    }
    part1_valid_passports += current_passport.is_valid();  // Catch last passport
    passports.push_back(current_passport);

    // Part 2
    int part2_valid_passports = 0;
    for (passport p : passports) {
        part2_valid_passports += (p.birth_year.length() == 4 && between(p.birth_year, 1920, 2002))
            && (p.issue_year.length() == 4 && between(p.issue_year, 2010, 2020))
            && (p.expiration_year.length() == 4 && between(p.expiration_year, 2020, 2030))
            && (p.height.length() != 0 && valid_height(p.height))
            && (p.hair_colour.length() == 7 && valid_hair(p.hair_colour))
            && (EYE_CLRS.find(p.eye_colour) != EYE_CLRS.end())
            && (p.passport_id.length() == 9 && all_of(p.passport_id.begin(), p.passport_id.end(), ::isdigit));
    }

    cout << "Part 1: " << part1_valid_passports << endl;
    cout << "Part 2: " << part2_valid_passports << endl;
    return 0;
}