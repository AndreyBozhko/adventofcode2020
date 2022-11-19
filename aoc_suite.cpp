#include "aoc_suite.h"

using namespace std;


Aoc::PreparedSolution& Aoc::PreparedSolution::PrintResults(ostream& out) {
    out << solver_->GetDay() << ", Part A: "
        << (cachedA ? *cachedA : solver_->SolveA()) << '\n'
        << solver_->GetDay() << ", Part B: "
        << (cachedB ? *cachedB : solver_->SolveB()) << '\n'
        << endl;
    return *this;
}

Aoc::PreparedSolution& Aoc::PreparedSolution::ExpectA(const Result& v)  {
    assert(solver_->SolveA() == v);
    cachedA = v;
    return *this;
}

Aoc::PreparedSolution& Aoc::PreparedSolution::ExpectB(const Result& v)  {
    assert(solver_->SolveB() == v);
    cachedB = v;
    return *this;
}

Aoc::PreparedSolution Aoc::SolutionWrapper::Process(istream& in) {
    ptr_->ProcessInput(in);
    return PreparedSolution(std::move(ptr_));
}

Aoc::SolutionWrapper Aoc::SolutionWrapper::ForDay(Day day) {
    switch (day) {
        case Day::_01:
            return SolutionWrapper(make_unique<Day1Solver>());
        case Day::_02:
            return SolutionWrapper(make_unique<Day2Solver>());
        case Day::_03:
            return SolutionWrapper(make_unique<Day3Solver>());
        case Day::_04:
            return SolutionWrapper(make_unique<Day4Solver>());
        case Day::_05:
            return SolutionWrapper(make_unique<Day5Solver>());
        case Day::_06:
            return SolutionWrapper(make_unique<Day6Solver>());
        case Day::_07:
            return SolutionWrapper(make_unique<Day7Solver>());
        case Day::_08:
            return SolutionWrapper(make_unique<Day8Solver>());
        case Day::_09:
            return SolutionWrapper(make_unique<Day9Solver>());
        case Day::_10:
            return SolutionWrapper(make_unique<Day10Solver>());
        case Day::_11:
            return SolutionWrapper(make_unique<Day11Solver>());
        case Day::_12:
            return SolutionWrapper(make_unique<Day12Solver>());
        case Day::_13:
            return SolutionWrapper(make_unique<Day13Solver>());
        case Day::_14:
            return SolutionWrapper(make_unique<Day14Solver>());
        case Day::_15:
            return SolutionWrapper(make_unique<Day15Solver>());
        case Day::_16:
            return SolutionWrapper(make_unique<Day16Solver>());
        case Day::_17:
            return SolutionWrapper(make_unique<Day17Solver>());
        case Day::_18:
            return SolutionWrapper(make_unique<Day18Solver>());
        case Day::_19:
            return SolutionWrapper(make_unique<Day19Solver>());
        case Day::_20:
            return SolutionWrapper(make_unique<Day20Solver>());
        case Day::_21:
            return SolutionWrapper(make_unique<Day21Solver>());
        case Day::_22:
            return SolutionWrapper(make_unique<Day22Solver>());
        case Day::_23:
            return SolutionWrapper(make_unique<Day23Solver>());
        case Day::_24:
            return SolutionWrapper(make_unique<Day24Solver>());
        case Day::_25:
            return SolutionWrapper(make_unique<Day25Solver>());
        default:
            throw runtime_error("It's XMAS already!");
    }
}
