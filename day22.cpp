#include "adventofcode.h"

#include <sstream>

using namespace std;


void Aoc::Day22Solver::ProcessInput(istream& in) {
    string s;
    auto* deck = &deck1;
    while (getline(in, s)) {
        if (s.empty()) {
            deck = &deck2;
            continue;
        }
        if (s[0] == 'P') continue;
        deck->push_back(stoi(s));
    }
}

int Aoc::Day22Solver::ComputeScore(const std::deque<int>& d) {
    int res = 0, sz = (int) d.size();
    for (int n : d) {
        res += n * sz--;
    }
    return res;
}

Result Aoc::Day22Solver::SolveA() const {
    auto d1 = deck1, d2 = deck2;
    while (!d1.empty() && !d2.empty()) {
        int n1 = d1.front(), n2 = d2.front();
        d1.pop_front(), d2.pop_front();
        deque<int>& d = n1 > n2 ? d1 : d2;
        d.push_back(max(n1, n2));
        d.push_back(min(n1, n2));
    }
    return ComputeScore(d1.empty() ? d2 : d1);
}

string Aoc::Day22Solver::ComputeState(const deque<int>& d1, const deque<int>& d2) {
    ostringstream out;
    for (int i : d1) out << i << ',';
    out << "-,";
    for (int i : d2) out << i << ',';
    return out.str();
}

Aoc::Day22Solver::Player Aoc::Day22Solver::Recurse(deque<int>& d1, deque<int>& d2) {
    unordered_set<string> seen;

    while (!d1.empty() && !d2.empty()) {
        auto state = ComputeState(d1, d2);
        if (seen.count(state) != 0) {
            return Player::FIRST;
        }
        seen.insert(state);

        int n1 = d1.front(), n2 = d2.front();
        d1.pop_front(), d2.pop_front();
        if (n1 <= (int) d1.size() && n2 <= (int) d2.size()) {
            deque<int> d1_copy = {d1.begin(), d1.begin() + n1};
            deque<int> d2_copy = {d2.begin(), d2.begin() + n2};
            auto winner = Recurse(d1_copy, d2_copy);
            if (winner == Player::FIRST) {
                d1.push_back(n1); d1.push_back(n2);
            } else {
                d2.push_back(n2); d2.push_back(n1);
            }
        } else {
            deque<int>& d = n1 > n2 ? d1 : d2;
            d.push_back(max(n1, n2));
            d.push_back(min(n1, n2));
        }
    }

    return d2.empty() ? Player::FIRST : Player::SECOND;
}

Result Aoc::Day22Solver::SolveB() const {
    auto d1 = deck1, d2 = deck2;
    Recurse(d1, d2);
    return ComputeScore(d1.empty() ? d2 : d1);
}
