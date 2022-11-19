#include "adventofcode.h"

#include <cassert>

using namespace std;


template <typename InputIt, typename Test>
int LocatePosition(InputIt first, InputIt last, Test test) {
    int l = 0, mid, r = 1u << (size_t) distance(first, last);
    for (auto it = first; it != last; it++) {
        mid = (l + r) / 2;
        if (test(*it)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return l;
}


void Aoc::Day5Solver::ProcessInput(istream& in) {
    string s;
    while (getline(in, s)) {
        auto seat = ParseSeat(s);
        ids.push_back(seat.first * 8 + seat.second);
    }

    sort(ids.begin(), ids.end());
    maxId = *ids.rbegin();

    auto it = adjacent_find(ids.begin(), ids.end(), [](int l, int r) { return l + 2 == r; } );
    actualId = *it+1;
}

pair<int, int> Aoc::Day5Solver::ParseSeat(const string& s) {
    assert(s.size() == 10);
    return {
        LocatePosition(s.begin(), s.begin() + 7,  [](char c) { return c == 'B'; }),
        LocatePosition(s.begin() + 7, s.end(), [](char c) { return c == 'R'; })
    };
}

Result Aoc::Day5Solver::SolveA() const {
    return maxId;
}

Result Aoc::Day5Solver::SolveB() const {
    return actualId;
}
