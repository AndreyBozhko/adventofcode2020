#include "adventofcode.h"

#include <sstream>

using namespace std;


void Aoc::Day23Solver::ProcessInput(istream& in) {
    string s;
    in >> s;
    for (char c : s) original_cups.push_back(c - '0');
}

Result Aoc::Day23Solver::SolveA() const {
    auto cups = original_cups;
    PlayGame(cups, 100, *max_element(cups.begin(), cups.end()));

    ostringstream out;
    auto it = next(find(cups.begin(), cups.end(), 1));
    for (size_t i = 1; i < cups.size(); i++, it++) {
        if (it == cups.end()) it = cups.begin();
        out << *it;
    }
    return out.str();
}

Result Aoc::Day23Solver::SolveB() const {
    auto cups = original_cups;
    int max_el = 1'000'000;
    for (int el = *max_element(cups.begin(), cups.end()) + 1; el <= max_el; el++) {
        cups.push_back(el);
    }
    PlayGame(cups, 10'000'000, max_el);
    auto it = next(find(cups.begin(), cups.end(), 1));
    int64_t res = 1;
    for (auto j = 0; j < 2; j++, it++) {
        if (it == cups.end()) it = cups.begin();
        res *= (int64_t) *it;
    }
    return res;
}

void Aoc::Day23Solver::PlayGame(list<int>& cups, size_t rounds, int max_el) {
    vector<ListIterator> num_to_iter(cups.size() + 1);
    for (auto it = cups.begin(); it != cups.end(); it++) num_to_iter[*it] = it;

    auto cur = cups.begin();
    for (size_t step = 1; step <= rounds; step++) {
        vector<ListIterator> new_pick(3);
        {
            auto jt = next(cur);
            for (auto j = 0; j < 3; j++, jt++) {
                if (jt == cups.end()) jt = cups.begin();
                new_pick[j] = jt;
            }
        }
        // find destination
        int dest_cup = *cur - 1;
        while (dest_cup <= 0 || any_of(new_pick.begin(), new_pick.end(),
                                       [dest_cup](auto x) { return *x == dest_cup; })) {
            if (--dest_cup <= 0) dest_cup = max_el;
        }
        auto dest = next(num_to_iter[dest_cup]);
        // move elements and update iterator mapping
        for (const auto& el : new_pick) {
            dest = cups.insert(dest, *el);
            num_to_iter[*dest] = dest;
            cups.erase(el);
            dest++;
        }

        if (++cur == cups.end()) cur = cups.begin();
    }
}
