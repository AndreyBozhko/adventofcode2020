#pragma once

#include <string>
#include <unordered_map>
#include <vector>


class BootCode {
public:
    enum class Op {
        ACC, JMP, NOP
    };

    struct Instruction {
        Op operation;
        int argument;

        static Instruction FromString(const std::string& s);
        static const std::unordered_map<std::string, Op> MAPPING;
    };

    struct ProgramReturn {
        int accumulator = 0;
        bool error = false;
    };

public:
    BootCode() = default;
    explicit BootCode(int acc) : accumulator(acc) {}

    ProgramReturn Run(const std::vector<Instruction>& instr);
    void Reset(int acc);
private:
    int accumulator = 0;
};
