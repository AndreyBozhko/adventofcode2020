#include "adventofcode.h"

using namespace std;


void Aoc::Day6Solver::ProcessInput(istream& in) {
    countA = countB = 0;
    int group_size = 0;
    vector<int> answers(26);

    string s;
    while (getline(in, s)) {
        // an extra newline was added to the input for convenience
        if (!s.empty()) {
            group_size++;
            for (char c : s) {
                answers[c-'a']++;
            }
        } else {
            countA += count_if(answers.begin(), answers.end(), [](int x) { return x > 0; });
            countB += count(answers.begin(), answers.end(), group_size);
            fill(answers.begin(), answers.end(), 0);
            group_size = 0;
        }
    }
}

Result Aoc::Day6Solver::SolveA() const {
    return countA;
}

Result Aoc::Day6Solver::SolveB() const {
    return countB;
}
