#include "adventofcode.h"

#include <unordered_set>

using namespace std;


void Aoc::Day1Solver::ProcessInput(istream& in) {
    string s;
    while (getline(in, s)) {
        numbers.push_back(stoi(s));
    }
}

Result Aoc::Day1Solver::SolveA() const {
    unordered_set<int> seen;
    for (auto x : numbers) {
        if (seen.count(TARGET - x) != 0) {
            return x * (TARGET - x);
        }
        seen.insert(x);
    }
    throw runtime_error("unreachable");
}

Result Aoc::Day1Solver::SolveB() const {
    unordered_set<int> seen;
    for (size_t i = 0; i < numbers.size(); i++) {
        for (size_t j = 0; j < i; j++) {
            if (seen.count(TARGET - numbers[i] - numbers[j]) != 0) {
                return (TARGET - numbers[i] - numbers[j]) * numbers[i] * numbers[j];
            }
            seen.insert(numbers[i]);
        }
    }
    throw runtime_error("unreachable");
}
