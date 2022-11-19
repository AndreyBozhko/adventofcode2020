#include "adventofcode.h"

#include <sstream>

using namespace std;


void Aoc::Day3Solver::ProcessInput(istream& in) {
    string s;
    while (getline(in, s)) {
        tree_map.push_back(std::move(s));
    }
}


Result Aoc::Day3Solver::SolveA() const {
    auto slope = slopes.at(1);
    return CountTreesForSlope(slope.first, slope.second);
}

Result Aoc::Day3Solver::SolveB() const {
    int product = 1;
    for (const auto& slope : slopes) {
        product *= CountTreesForSlope(slope.first, slope.second);
    }
    return product;
}

int Aoc::Day3Solver::CountTreesForSlope(int slope_x, int slope_y) const {
    int count = 0;
    int sz_x = tree_map.front().size();
    int sz_y = tree_map.size();
    for (int x = 0, y = 0; y < sz_y; y += slope_y, x += slope_x) {
        const auto& row = tree_map.at(y);
        if (row.at(x % sz_x) == '#') count++;
    }
    return count;
}
