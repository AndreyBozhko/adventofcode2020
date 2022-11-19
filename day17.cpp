#include "adventofcode.h"

#include <sstream>

using namespace std;


bool Aoc::Day17Solver::Point::operator== (const Point& other) const {
    return tie(x, y, z, t) == tie(other.x, other.y, other.z, other.t);
}
Aoc::Day17Solver::Point Aoc::Day17Solver::Point::operator+ (const Point& other) const {
    return {x + other.x, y + other.y, z + other.z, t + other.t};
}

size_t Aoc::Day17Solver::PointHasher::operator()(const Aoc::Day17Solver::Point &pt) const {
    return (((hasher(pt.x) * 1337) + hasher(pt.y)) * 1337 + hasher(pt.z)) * 1337 + hasher(pt.t);
}


void Aoc::Day17Solver::ProcessInput(istream& in) {
    string s;
    int y = 0, z = 0, t = 0;
    while (getline(in, s) && !s.empty()) {
        for (int x = 0; x < (int) s.size(); x++) {
            if (s[x] == '#') {
                grid.emplace(Point{x, y, z, t});
            }
        }
        y++;
    }
}

Result Aoc::Day17Solver::SolveA() const {
    auto active = grid;
    for (auto i = 0; i < 6; i++) {
        RunCycle(active, DXDYDZ);
    }
    return (int64_t) active.size();
}

Result Aoc::Day17Solver::SolveB() const {
    auto active = grid;
    for (auto i = 0; i < 6; i++) {
        RunCycle(active, DXDYDZDT);
    }
    return (int64_t) active.size();
}

void Aoc::Day17Solver::RunCycle(PointSet& active, const vector<Point>& deltas) {
    PointSet inserts, deletes, seen;
    for (const auto& pt : active) {
        // consider point and all neighbors since those may be inactive
        for (const auto& delta : deltas) {
            auto new_pt = pt + delta;
            if (seen.count(new_pt) != 0) continue;

            seen.insert(new_pt);
            auto res = ShouldChangeState(new_pt, active, deltas);
            if (res == Action::DELETE) deletes.insert(new_pt);
            else if (res == Action::INSERT) inserts.insert(new_pt);
        }
    }

    for (const auto& el : deletes) active.erase(el);
    for (const auto& el : inserts) active.insert(el);
}

Aoc::Day17Solver::Action
Aoc::Day17Solver::ShouldChangeState(Point pt, const PointSet& active, const vector<Point> &deltas) {
    int active_n = 0;
    for (size_t i = 1; i < deltas.size(); i++) {
        if (active.count(pt + deltas[i]) != 0) active_n++;
    }

    if (active.count(pt) != 0) {
        if (active_n < 2 || active_n > 3) return Action::DELETE;
    } else {
        if (active_n == 3) return Action::INSERT;
    }

    return Action::NONE;
}

const vector<Aoc::Day17Solver::Point> Aoc::Day17Solver::DXDYDZ = [](){
    vector<int> choices {-1, 0, 1};
    vector<Point> tmp; tmp.reserve(27);
    for (int x : choices)
        for (int y : choices)
            for (int z : choices)
                tmp.push_back({x, y, z, 0});
    // ZERO is always in the beginning
    partition(tmp.begin(), tmp.end(), [](const Point& pt) { return pt == ZERO; });
    return tmp;
}();

const vector<Aoc::Day17Solver::Point> Aoc::Day17Solver::DXDYDZDT = []() {
    vector<int> choices {-1, 0, 1};
    vector<Point> tmp; tmp.reserve(81);
    for (int x : choices)
        for (int y : choices)
            for (int z : choices)
                for (int t : choices)
                    tmp.push_back({x, y, z, t});
    // ZERO is always in the beginning
    partition(tmp.begin(), tmp.end(), [](const Point& pt) { return pt == ZERO; });
    return tmp;
}();
