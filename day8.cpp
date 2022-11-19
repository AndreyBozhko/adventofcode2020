#include "adventofcode.h"

using namespace std;


void Aoc::Day8Solver::ProcessInput(istream& in) {
    string s;
    while (getline(in, s)) {
        instr.emplace_back(BootCode::Instruction::FromString(s));
    }
}

Result Aoc::Day8Solver::SolveA() const {
    return BootCode().Run(instr).accumulator;
}

Result Aoc::Day8Solver::SolveB() const {
    auto program = BootCode();
    auto instr_copy = instr;

    for (size_t i = 0; i < instr_copy.size(); i++) {
        auto& el = instr_copy[i];
        switch (el.operation) {
            case BootCode::Op::ACC:
                break;
            default:
                program.Reset(0);
                el.operation = SWITCH_MATRIX.at(el.operation);
                auto result = program.Run(instr_copy);
                if (result.error) {
                    return result.accumulator;
                }
                el.operation = SWITCH_MATRIX.at(el.operation);
        }
    }
    throw runtime_error("unreachable");
}

const std::unordered_map<BootCode::Op, BootCode::Op> Aoc::Day8Solver::SWITCH_MATRIX = {
        {BootCode::Op::NOP, BootCode::Op::JMP},
        {BootCode::Op::JMP, BootCode::Op::NOP}
};
