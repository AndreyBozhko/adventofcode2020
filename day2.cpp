#include "adventofcode.h"

#include <sstream>

using namespace std;


void Aoc::Day2Solver::ProcessInput(istream& in) {
    string s;
    validA = validB = 0;

    while (getline(in, s)) {
        istringstream istream(s);
        int a, b; char c; string pwd;

        istream >> a; istream.ignore(1);
        istream >> b; istream.ignore(1);
        istream >> c; istream.ignore(2);
        istream >> pwd;

        auto ans = count(pwd.begin(), pwd.end(), c);
        if (a <= ans && ans <= b) validA++;

        if (pwd.at(a-1) == c && pwd.at(b-1) != c) validB++;
        if (pwd.at(a-1) != c && pwd.at(b-1) == c) validB++;
    }
}


Result Aoc::Day2Solver::SolveA() const {
    return validA;
}

Result Aoc::Day2Solver::SolveB() const {
    return validB;
}
