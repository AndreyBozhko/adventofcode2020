#pragma once

#include "adventofcode.h"
#include "utils.h"

#include <cassert>
#include <iostream>
#include <memory>


namespace Aoc {

    class PreparedSolution {
    public:
        explicit PreparedSolution(std::unique_ptr<Aoc::Solver> solver)
            : solver_(std::move(solver)), cachedA(std::nullopt), cachedB(std::nullopt) {}
        PreparedSolution& PrintResults(std::ostream& out);
        PreparedSolution& ExpectA(const Result& v);
        PreparedSolution& ExpectB(const Result& v);
    private:
        std::unique_ptr<Aoc::Solver> solver_;
        std::optional<Result> cachedA, cachedB;
    };


    class SolutionWrapper {
    public:
        PreparedSolution Process(std::istream& in);
        static SolutionWrapper ForDay(Day day);
    private:
        explicit SolutionWrapper(std::unique_ptr<Solver> ptr) : ptr_(std::move(ptr)) {}
        std::unique_ptr<Solver> ptr_ = nullptr;
    };

}
