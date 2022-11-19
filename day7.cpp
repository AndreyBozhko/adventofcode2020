#include "adventofcode.h"

#include <stack>
#include <sstream>

using namespace std;


void Aoc::Day7Solver::ProcessInput(istream& in) {
    mapping.clear();
    inverted_mapping.clear();

    string s;
    while (getline(in, s)) {
        istringstream istream(s);
        string w1, w2, num;
        getline(istream, w1, ' '); getline(istream, w2, ' ');
        istream.ignore(13);
        getline(istream, num, ' ');
        w1.append(" "); w1.append(w2);

        auto& m = mapping[w1];
        if (num != "no") {
            string rest;
            getline(istream, rest, '\n');
            num.append(" "); num.append(rest); rest = std::move(num);

            size_t left = 0, right = 0;
            do {
                right = rest.find(',', right);
                string tmp = rest.substr(left, right);
                int cnt; string ww1, ww2;
                istringstream istream2(tmp);
                istream2 >> cnt >> ww1 >> ww2;
                ww1.append(" "); ww1.append(ww2);
                m[ww1] = cnt;
                if (right != string::npos) right += 2;
                left = right;
            } while (left != string::npos);
        }
    }

    for (const auto& p : mapping) {
        for (const auto &inside : p.second) {
            inverted_mapping[inside.first].insert(p.first);
        }
    }
}

int Aoc::Day7Solver::CountInside(const std::string& bag) const {
    int total = 0;
    if (mapping.count(bag) == 0) {
        return total;
    }

    for (const auto& el : mapping.at(bag)) {
        total += (CountInside(el.first) + 1) * el.second;
    }
    return total;
}

Result Aoc::Day7Solver::SolveA() const {
    unordered_set<string> all_bags;
    stack<string> st; st.push(MY_BAG);

    while (!st.empty()) {
        auto el = st.top(); st.pop();

        if (inverted_mapping.count(el) == 0) continue;
        for (const auto& x : inverted_mapping.at(el)) {
            if (all_bags.count(x) == 0) {
                st.push(x);
                all_bags.insert(x);
            }
        }
    }

    return (int) all_bags.size();
}

Result Aoc::Day7Solver::SolveB() const {
    return CountInside(MY_BAG);
}
