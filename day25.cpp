#include "adventofcode.h"

#include <sstream>

using namespace std;


void Aoc::Day25Solver::ProcessInput(istream& in) {
    int64_t num;
    for (int i = 0; i < 2; i++) {
        in >> num;
        devices.push_back(Device::FromPublicKey(num));
    }
}

Result Aoc::Day25Solver::SolveA() const {
    return devices[0].GenerateEncryptionKey(devices[1].GeneratePublicKey());
}

Result Aoc::Day25Solver::SolveB() const {
    return "It's over now!";
}

int64_t Aoc::Day25Solver::Device::GenerateEncryptionKey(int64_t subject_number) const {
    int64_t res = 1;
    for (int i = 0; i < loop; i++) {
        res = (res * subject_number) % modulus;
    }
    return res;
}

int64_t Aoc::Day25Solver::Device::GeneratePublicKey() const {
    return GenerateEncryptionKey(subject);
}

Aoc::Day25Solver::Device Aoc::Day25Solver::Device::FromPublicKey(int64_t pubkey) {
    Device d;
    int64_t p = 1;
    do {
        d.loop++;
        p = (p * d.subject) % d.modulus;
    } while (p != pubkey);
    return d;
}
