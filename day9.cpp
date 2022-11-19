#include "adventofcode.h"

using namespace std;


void Aoc::Day9Solver::ProcessInput(istream& in) {
    int num;
    while (in >> num) {
        sequence.push_back(num);
    }
    preamble = (sequence.size() < 25) ? 5 : 25;

    weaknessA = FindWeaknessA(sequence, preamble);
    weaknessB = FindWeaknessB(sequence, weaknessA);
}

Result Aoc::Day9Solver::SolveA() const {
    return weaknessA;
}

Result Aoc::Day9Solver::SolveB() const {
    return weaknessB;
}

int Aoc::Day9Solver::FindWeaknessA(const vector<int>& seq, int preamble) {
    for (size_t i = preamble; i < seq.size(); i++) {
        unordered_set<int> seen;
        int target = seq[i];
        bool flag = false;
        for (size_t j = i - preamble; j < i; j++) {
            if (seen.count(target - seq[j]) != 0) {
                flag = true;
                break;
            }
            seen.insert(seq[j]);
        }
        if (!flag) {
            return target;
        }
    }
    throw runtime_error("unreachable");
}

int Aoc::Day9Solver::FindWeaknessB(const vector<int>& seq, int target) {
    size_t left = 0, right = 1;
    int sum = seq[0];
    while (left + 1 < seq.size() && right <= seq.size()) {
        if (sum == target && left + 2 <= right) {
            auto [l, r] = minmax_element(seq.begin() + left, seq.begin() + right);
            if (*l != *r) {
                return *l + *r;
            } else {
                // do something
            }
        } else if (sum < target) {
            while (sum < target && right <= seq.size()) {
                sum += seq[right++];
            }
        } else if (sum > target) {
            while (sum > target && left < right) {
                sum -= seq[left++];
            }
        } else {
            // do something
        }
    }
    throw runtime_error("unreachable");
}
