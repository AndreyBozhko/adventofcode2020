#include "adventofcode.h"

#include <sstream>

using namespace std;


void Aoc::Day18Solver::ProcessInput(istream& in) {
    string s;
    while (getline(in, s)) {
        istringstream istream(s);
        Expression parsed;
        while (istream.peek() != -1) {
            char c; istream >> c;
            if (c == ' ') continue;
            else if (c == '+' || c == '*') parsed.emplace_back(static_cast<Op>(c));
            else if (c == '(' || c == ')') parsed.emplace_back(static_cast<Bracket>(c));
            else {
                istream.putback(c);
                Number num; istream >> num;
                parsed.emplace_back(num);
            }
        }
        expressions.push_back(std::move(parsed));
    }
}

Aoc::Day18Solver::Number Aoc::Day18Solver::EvaluateLeftToRight(Iterator left, Iterator right) {
    Number ans = 0;
    Op op = Op::ADD;

    for (auto it = left; it != right; it++) {
        if (holds_alternative<Op>(*it)) {
            op = get<Op>(*it);
            continue;
        }
        Number num;
        if (holds_alternative<Number>(*it)) {
            num = get<Number>(*it);
        } else {
            // must be left bracket
            auto jt = FindMatchingClosingBracket(it);
            num = EvaluateLeftToRight(next(it), prev(jt));
            it = prev(jt);
        }
        // do the math
        if (op == Op::ADD) ans += num;
        else ans *= num;
    }
    return ans;
}

Aoc::Day18Solver::Number Aoc::Day18Solver::EvaluateAddFirst(Iterator left, Iterator right) {
    Expression tmp;
    for (auto it = left; it != right; it++) {
        if (holds_alternative<Op>(*it)) {
            tmp.push_back(*it);
            continue;
        }
        Number num;
        if (holds_alternative<Number>(*it)) {
            num = get<Number>(*it);
        } else {
            // must be left bracket
            auto jt = FindMatchingClosingBracket(it);
            num = EvaluateAddFirst(next(it), prev(jt));
            it = prev(jt);
        }
        // eagerly evaluate addition
        if (!tmp.empty() && get<Op>(tmp.back()) == Op::ADD) {
            tmp.pop_back();
            num += get<Number>(tmp.back());
            tmp.pop_back();
        }
        tmp.push_back(Number{num});
    }
    return EvaluateLeftToRight(tmp.begin(), tmp.end());
}

Result Aoc::Day18Solver::SolveA() const {
    Number result = 0;
    for_each(expressions.begin(), expressions.end(),
             [&result](const auto& exp) { result += EvaluateLeftToRight(exp.begin(), exp.end()); });
    return result;
}

Result Aoc::Day18Solver::SolveB() const {
    Number result = 0;
    for_each(expressions.begin(), expressions.end(),
             [&result](const auto& exp) { result += EvaluateAddFirst(exp.begin(), exp.end()); });
    return result;
}

Aoc::Day18Solver::Iterator Aoc::Day18Solver::FindMatchingClosingBracket(Iterator left) {
    int cnt = 1;
    auto jt = next(left);
    while (cnt != 0) {
        if (holds_alternative<Bracket>(*jt)) {
            if (get<Bracket>(*jt) == Bracket::LEFT) cnt++;
            else cnt--;
        }
        jt++;
    }
    return jt;
}
