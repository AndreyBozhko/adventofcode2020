#include "adventofcode.h"

using namespace std;


void Aoc::Day10Solver::ProcessInput(istream& in) {
    int num;
    sequence.assign(1, 0);
    while (in >> num) {
        sequence.push_back(num);
    }
    sort(sequence.begin(), sequence.end());
    sequence.push_back(sequence.back() + 3);
}

Result Aoc::Day10Solver::SolveA() const {
    vector<int> diff(4, 0);
    for (size_t i = 1; i < sequence.size(); i++) {
        diff[sequence[i] - sequence[i-1]]++;
    }
    return diff[1] * diff[3];
}

Result Aoc::Day10Solver::SolveB() const {
    vector<int64_t> total(sequence.size(), 0);
    total[0] = 1;
    for (size_t i = 0; i < sequence.size(); i++) {
        for (size_t j = 1; j <= 3 && i >= j && sequence[i - j] + 3 >= sequence[i]; j++) {
            total[i] += total[i-j];
        }
    }
    return total.back();
}
