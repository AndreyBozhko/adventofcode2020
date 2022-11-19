#include "adventofcode.h"

#include <sstream>

using namespace std;


bool Aoc::Day4Solver::CheckIfPresent(const unordered_map<string, string>& data) {
    return (data.size() == 8 || (data.size() == 7 && data.count("cid") == 0));
}

bool Aoc::Day4Solver::CheckIfValid(const unordered_map<string, string>& data) {
    bool fl = true;

    auto byr = data.at("byr");
    fl = fl && byr.size() == 4 && stoi(byr) >= 1920 && stoi(byr) <= 2002;

    auto iyr = data.at("iyr");
    fl = fl && iyr.size() == 4 && stoi(iyr) >= 2010 && stoi(iyr) <= 2020;

    auto eyr = data.at("eyr");
    fl = fl && eyr.size() == 4 && stoi(eyr) >= 2020 && stoi(eyr) <= 2030;

    auto hgt = data.at("hgt");
    {
        istringstream s(hgt);
        int i; string unit; s >> i >> unit;
        fl = fl && ((unit == "cm" && 150 <= i && i <= 193)
                    || (unit == "in" && 59 <= i && i <= 76));
    }

    auto hcl = data.at("hcl");
    fl = fl && hcl.size() == 7
            && all_of(next(hcl.begin()), hcl.end(),
                      [](char d) { return ('0' <= d && d <= '9') || ('a' <= d && d <= 'f'); });

    const unordered_set<string> ecl {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    fl = fl && ecl.count(data.at("ecl")) != 0;

    auto pid = data.at("pid");
    fl = fl && pid.size() == 9
            && all_of(pid.begin(), pid.end(),
                      [](char d) { return '0' <= d && d <= '9'; });

    return fl;
}


void Aoc::Day4Solver::ProcessInput(istream& in) {
    string k, v, line;
    unordered_map<string, string> data;
    while (in) {
        getline(in, line);
        if (line.empty()) {
            if (CheckIfPresent(data)) {
                countA++;
                if (CheckIfValid(data)) {
                    countB++;
                }
            }
            data.clear();
        } else {
            istringstream linestream(line);
            while (linestream.peek() != -1) {
                getline(linestream, k, ':');
                getline(linestream, v, ' ');
                data[std::move(k)] = std::move(v);
            }
        }
    }
}

Result Aoc::Day4Solver::SolveA() const {
    return countA;
}

Result Aoc::Day4Solver::SolveB() const {
    return countB;
}

