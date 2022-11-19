#include "adventofcode.h"

#include <numeric>

using namespace std;


void Aoc::Day13Solver::ProcessInput(istream& in) {
    string s;

    getline(in, s);
    ts = stoi(s);

    getline(in, s);
    size_t left = 0;
    do {
        auto right = s.find(',', left);
        if (s[left] == 'x') {
            bus_ids.emplace_back();
        } else {
            bus_ids.emplace_back(stoi(s.substr(left, right - left)));
        }
        left = right == string::npos ? right : right + 1;
    } while (left != string::npos);
}

Result Aoc::Day13Solver::SolveA() const {
    int id = -1, wait = -1;

    for (const auto& bus : bus_ids) {
        if (!bus) continue;
        int b = *bus;
        int rem = ts % b; if (rem > 0) rem = b - rem;
        if (wait < 0 || wait > rem) {
            wait = rem; id = b;
        }
    }

    return id * wait;
}

Result Aoc::Day13Solver::SolveB() const {
    int64_t result = 0, step = 1;

    for (int i = 0; i < (int) bus_ids.size(); i++) {
        if (!bus_ids[i]) continue;
        int bus = *bus_ids[i];
        while ((result + i) % bus != 0) result += step;
        step = lcm(step, bus);
    }
    return result;
}
