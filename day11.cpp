#include "adventofcode.h"

using namespace std;


void Aoc::Day11Solver::ProcessInput(istream& in) {
    string s;
    while (getline(in, s)) {
        seats.emplace_back(s.size());
        auto& row = seats.back();
        for (size_t i = 0; i < s.size(); i++) {
            row[i] = static_cast<Seat>(s[i]);
        }
    }
}

Result Aoc::Day11Solver::SolveA() const {
    return Simulate(seats, {}, 4);
}

Result Aoc::Day11Solver::SolveB() const {
    return Simulate(seats, {Seat::FLOOR}, 5);
}

int Aoc::Day11Solver::CountNeighbors(const vector<vector<Seat>>& seats,
                                     size_t i, size_t j, const set<Seat>& continue_on) {
    int ans = 0;

    for (const auto& [dx, dy] : DXDY) {
        for (size_t ii = i, jj = j;
             ii >= 0 && ii < seats.size() && jj >= 0 && jj < seats[0].size();
             ii += dx, jj += dy) {
            if (tie(ii, jj) != tie(i, j) && continue_on.count(seats[ii][jj]) == 0) {
                if (seats[ii][jj] == Seat::TAKEN) ans++;
                break;
            }
            if (dx < 0 && ii == 0) break;
            if (dy < 0 && jj == 0) break;
        }
    }

    return ans;
}

int Aoc::Day11Solver::Simulate(vector<vector<Seat>> seats, const set<Seat>& continue_on, int max_tolerance) {
    int ans = 0;
    while (true) {
        auto seats_copy = seats;
        int changed = 0;
        for (size_t i = 0; i < seats.size(); i++) {
            for (size_t j = 0; j < seats[i].size(); j++) {
                auto count = CountNeighbors(seats, i, j, continue_on);
                if (seats[i][j] == Seat::EMPTY && count == 0) {
                    seats_copy[i][j] = Seat::TAKEN;
                    ans++;
                    changed++;
                } else if (seats[i][j] == Seat::TAKEN && count >= max_tolerance) {
                    seats_copy[i][j] = Seat::EMPTY;
                    ans--;
                    changed++;
                }
            }
        }
        if (changed == 0) break;
        seats = std::move(seats_copy);
    }
    return ans;
}

const vector<pair<int, int>> Aoc::Day11Solver::DXDY {
        {0,1}, {0, -1}, {1, 0}, {-1, 0},
        {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
};
