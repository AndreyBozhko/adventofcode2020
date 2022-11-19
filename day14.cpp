#include "adventofcode.h"

#include <algorithm>
#include <sstream>
#include <cmath>

using namespace std;

void Aoc::Day14Solver::ProcessInput(istream& in) {
    string s;
    while (getline(in, s)) {
        if (s[1] == 'a') {
            instructions.emplace_back(Mask{s.substr(7)});
        } else {
            int64_t addr, num;
            istringstream istream(s);
            istream.ignore(4); istream >> addr;
            istream.ignore(4); istream >> num;
            instructions.emplace_back(MemoryAccess{Address{addr}, Value{num}});
        }
    }
}

Result Aoc::Day14Solver::SolveA() const {
    unordered_map<uint64_t, uint64_t> memory;
    Mask mask;
    for (const auto& instr : instructions) {
        if (holds_alternative<Mask>(instr)) {
            mask = get<Mask>(instr);
        } else {
            const auto& ma = get<MemoryAccess>(instr);
            memory[ma.addr.value] = mask(ma.value);
        }
    }
    int64_t result = 0;
    for (const auto& kv : memory) {
        result += kv.second;
    }

    return result;
}

Result Aoc::Day14Solver::SolveB() const {
    unordered_map<size_t, size_t> memory;
    Mask mask;
    for (const auto& instr : instructions) {
        if (holds_alternative<Mask>(instr)) {
            mask = get<Mask>(instr);
        } else {
            const auto& ma = get<MemoryAccess>(instr);
            for (auto q : mask(ma.addr)) {
                memory[q] = ma.value.value;
            }
        }
    }
    int64_t result = 0;
    for (const auto& kv : memory) {
        result += kv.second;
    }

    return result;
}

uint64_t Aoc::Day14Solver::Mask::operator() (const Value& val) const {
    uint64_t n_and = 0, n_or = 0;
    for (size_t i = 0; i < 36; i++) {
        uint64_t shift = 1;
        shift <<= i;
        if (value[35-i] != '0') {
            n_and += shift;
        }
        if (value[35-i] == '1') {
            n_or += shift;
        }
    }
    uint64_t res1, res2;
    res1 = (val.value & n_and);
    res2 = (res1 | n_or);

    return res2;
}

void Recurse(unordered_set<uint64_t>& results, uint64_t res1, const vector<uint64_t>& shifts, size_t i) {
    if (i == shifts.size()) {
        results.insert(res1);
        return;
    }
    auto shift = shifts[i];
    Recurse(results, (res1 | shift), shifts, i+1);
    Recurse(results, (res1 | shift) - shift, shifts, i+1);
}

vector<uint64_t> Aoc::Day14Solver::Mask::operator() (const Address& addr) const {
    vector<uint64_t> shifts;
    unordered_set<uint64_t> results;

    uint64_t n_or = 0;
    for (size_t i = 0; i < 36; i++) {
        uint64_t shift = 1;
        shift <<= i;
        if (value[35-i] == '1') {
            n_or += shift;
        }
        if (value[35-i] == 'X') {
            shifts.push_back(shift);
        }
    }
    uint64_t res1 = (addr.value | n_or);
    Recurse(results, res1, shifts, 0);

    return {results.begin(), results.end()};
}
