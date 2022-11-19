#include "adventofcode.h"

#include <algorithm>
#include <numeric>
#include <sstream>

using namespace std;


void Aoc::Day16Solver::ProcessInput(istream& in) {
    string s;
    int block = 0;
    while (getline(in, s)) {
        if (s.empty()) {
            block++;
            continue;
        }
        if (s == "your ticket:" || s == "nearby tickets:") continue;

        istringstream istream(s);
        if (block == 0) {
            char c;
            Rule rule;
            getline(istream, rule.field, ':');
            istream >> rule.a >> c >> rule.b;
            istream.ignore(4);
            istream >> rule.c >> c >> rule.d;
            rules.emplace_back(std::move(rule));
        } else {
            Ticket ticket;
            int x;
            while (istream.peek() != -1) {
                istream >> x; istream.ignore(1);
                ticket.push_back(x);
            }
            auto invalid_entries = IsInvalid(ticket);
            if (invalid_entries.empty()) {
                tickets.emplace_back(std::move(ticket));
            } else {
                ansA += accumulate(invalid_entries.begin(), invalid_entries.end(), 0);
            }
        }
    }
}

Result Aoc::Day16Solver::SolveA() const {
    return ansA;
}

Result Aoc::Day16Solver::SolveB() const {
    vector<unordered_set<string>> candidates(rules.size());

    for (int col = 0; col < (int) rules.size(); col++) {
        for (const auto& rule : rules) {
            bool flag = true;
            for (const auto& ticket : tickets) {
                flag = flag && rule(ticket[col]);
            }
            if (flag) { candidates[col].insert(rule.field); }
        }
    }

    vector<string> ordered_fields(rules.size());
    unordered_set<string> seen;

    for (int i = 1; i <= (int) rules.size(); i++) {
        auto it = find_if(candidates.begin(), candidates.end(), [i](const auto& c) { return (int) c.size() == i; });
        const auto& st = *it;
        auto field = *find_if(st.begin(), st.end(), [&seen](const auto& str) { return seen.count(str) == 0; });
        ordered_fields[distance(candidates.begin(), it)] = field;
        seen.insert(field);
    }

    int64_t res = 1;
    for (int i = 0; i < (int) rules.size(); i++) {
        if (ordered_fields[i].substr(0, 9) == "departure") {
            res *= (int64_t) tickets[0][i];
        }
    }

    return res;
}

bool Aoc::Day16Solver::Rule::operator()(int x) const {
    return (a <= x && x <= b) || (c <= x && x <= d);
}

vector<int> Aoc::Day16Solver::IsInvalid(const Ticket& ticket) const {
    vector<int> res;
    for (int x : ticket) {
        bool flag = any_of(rules.begin(), rules.end(), [x](const auto& rule) { return rule(x); });
        if (!flag) res.push_back(x);
    }
    return res;
}
