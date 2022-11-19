#include "adventofcode.h"

#include <algorithm>
#include <sstream>

using namespace std;

void Aoc::Day15Solver::ProcessInput(istream& in) {
    string s;
    while (getline(in, s, ',')) {
        sequence.push_back(stoi(s));
    }
}

Result Aoc::Day15Solver::SolveA() const {
    return SolveFor(sequence, 2020);
}

Result Aoc::Day15Solver::SolveB() const {
    return SolveFor(sequence, 30'000'000);
}

int64_t Aoc::Day15Solver::SolveFor(const vector<int64_t>& seq, int64_t pos) {
    unordered_map<int64_t, HeapOfTwo> history;
    int64_t i, last;
    for (i = 1; i <= (int64_t) seq.size(); i++) {
        history[seq[i - 1]].Push(i);
    }
    last = seq.back();
    while (i <= pos) {
        auto spoken = history.count(last) != 0;
        if (spoken) {
            const auto& hp = history.at(last);
            spoken = (hp.sz > 0 && hp.last != i-1) || (hp.sz > 1 && hp.last == i-1);
        }
        if (spoken) {
            const auto& hp = history.at(last);
            last = hp.last - hp.first;
        } else {
            last = 0;
        }
        history[last].Push(i++);
    }
    return last;
}

void Aoc::Day15Solver::HeapOfTwo::Push(int64_t num) {
    first = last;
    last = num;
    sz++;
}
