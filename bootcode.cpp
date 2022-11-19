#include "bootcode.h"

#include <unordered_set>

using namespace std;


const std::unordered_map<std::string, BootCode::Op> BootCode::Instruction::MAPPING = {
        {"acc", Op::ACC}, {"jmp", Op::JMP}, {"nop", Op::NOP}
};

BootCode::Instruction BootCode::Instruction::FromString(const string& s) {
    return {MAPPING.at(s.substr(0, 3)), stoi(s.substr(4))};
}

BootCode::ProgramReturn BootCode::Run(const vector<Instruction> &instr) {
    unordered_set<size_t> seen;

    for (size_t i = 0; i < instr.size(); ) {
        if (seen.count(i) != 0) {
            // encountered infinite loop
            return {accumulator, false};
        }
        seen.insert(i);

        auto& el = instr[i];
        switch (el.operation) {
            case Op::ACC:
                accumulator += el.argument;
                i++;
                break;
            case Op::JMP:
                i += el.argument;
                break;
            case Op::NOP:
                i++;
                break;
        }
    }
    // reached end of program
    return {accumulator, true};
}

void BootCode::Reset(int acc) {
    accumulator = acc;
}
