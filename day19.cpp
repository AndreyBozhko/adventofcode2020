#include "adventofcode.h"

#include <cassert>
#include <sstream>

using namespace std;


void Aoc::Day19Solver::ProcessInput(istream& in) {
    string s, rl;
    while (getline(in, s)) {
        if (s.empty()) break;
        auto pos = s.find(':');
        int idx = stoi(s.substr(0, pos));
        rl = s.substr(pos + 2);
        if (rl[0] == '"') {
            rules[idx] = make_unique<CharRule>(rl[1]);
        } else {
            auto sep = rl.find('|');
            if (sep == string::npos) {
                rules[idx] = make_unique<SeqRule>(rules, rl);
            } else {
                auto l = rl.substr(0, sep - 1), r = rl.substr(sep + 1);
                rules[idx] = make_unique<OrRule>(make_unique<SeqRule>(rules, l), make_unique<SeqRule>(rules, r));
            }
        }
    }
    while (getline(in, s)) {
        messages.push_back(std::move(s));
    }
}

Result Aoc::Day19Solver::SolveA() const {
    int64_t total = 0;
    const auto& rule0 = rules.at(0);
    for (const auto& msg : messages) {
        auto check = rule0->Match(msg, 0);
        if (check && *check == msg.size()) {
            total++;
        }
    }
    return total;
}

Result Aoc::Day19Solver::SolveB() const {
    int64_t total = 0;
    // rule 0 -> 8 11 -> x times (rule 42), y times (rule 42), y times (rule 31)
    const auto& rule42 = rules.at(42);
    const auto& rule31 = rules.at(31);
    size_t sz42 = rule42->GetSize(), sz31 = rule31->GetSize();

    for (const auto& msg : messages) {
        bool matched = false;
        for (size_t x = 1; x * sz42 + sz42 + sz31 <= msg.size() && !matched; x++) {
            for (size_t y = 1; x * sz42 + y * sz42 + y * sz31 <= msg.size() && !matched; y++) {
                bool ok = true;
                size_t cur = 0;

                for (size_t j = 0; j < x && ok; j++) {
                    auto check = rule42->Match(msg, cur);
                    if (!check) ok = false; else cur = *check;
                }
                for (size_t j = 0; j < y && ok; j++) {
                    auto check = rule42->Match(msg, cur);
                    if (!check) ok = false; else cur = *check;
                }
                for (size_t j = 0; j < y && ok; j++) {
                    auto check = rule31->Match(msg, cur);
                    if (!check) ok = false; else cur = *check;
                }
                if (ok && cur == msg.size()) matched = true;
            }
        }
        if (matched) total++;
    }
    return total;
}

optional<size_t> Aoc::Day19Solver::CharRule::Match(const string &s, size_t start) const {
    if (start < s.size() && s[start] == ch) return {start + 1};
    else return {};
}

size_t Aoc::Day19Solver::CharRule::GetSize() const { return 1; }

Aoc::Day19Solver::SeqRule::SeqRule(const unordered_map<int, unique_ptr<Rule>> &refs,
                                   const string &s) : references(refs) {
    istringstream istream(s);
    int idx;
    while (istream.peek() != -1) {
        istream >> idx;
        rule_idx.push_back(idx);
    }
}

optional<size_t> Aoc::Day19Solver::SeqRule::Match(const string &s, size_t pos) const {
    for (int idx : rule_idx) {
        auto res = references.at(idx)->Match(s, pos);
        if (!res) return {};
        pos = *res;
    }
    return {pos};
}

size_t Aoc::Day19Solver::SeqRule::GetSize() const {
    size_t sz = 0;
    for (int idx : rule_idx) {
        sz += references.at(idx)->GetSize();
    }
    return sz;
}

optional<size_t> Aoc::Day19Solver::OrRule::Match(const string &s, size_t start) const {
    auto r = left->Match(s, start);
    if (r) return r;
    r = right->Match(s, start);
    return r;
}

size_t Aoc::Day19Solver::OrRule::GetSize() const {
    assert(left->GetSize() == right->GetSize());
    return left->GetSize();
}
