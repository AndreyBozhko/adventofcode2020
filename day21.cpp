#include "adventofcode.h"

#include <deque>
#include <sstream>

using namespace std;


void Aoc::Day21Solver::ProcessInput(istream& in) {
    string s;
    vector<string> all_ingredients;
    while (getline(in, s)) {
        s.pop_back();
        istringstream istream(s);
        string tmp;
        set<string> ing;
        while (istream.peek() != -1) {
            while (istream.peek() != '(') {
                getline(istream, tmp, ' ');
                ing.insert(tmp);
                all_ingredients.push_back(std::move(tmp));
            }
            istream.ignore(10);
            while (istream >> tmp) {
                if (tmp.back() == ',') tmp.pop_back();
                if (allerg_to_ingr.count(tmp) == 0) {
                    allerg_to_ingr[tmp] = ing;
                } else {
                    vector<string> intersection(ing.size());
                    auto& old = allerg_to_ingr[tmp];
                    auto it = set_intersection(old.begin(), old.end(),
                                               ing.begin(), ing.end(),
                                               intersection.begin());
                    old = set<string>(intersection.begin(), it);
                }
            }
        }
    }

    unordered_set<string> may_contain_allerg;
    for (const auto& el : allerg_to_ingr) {
        for (const auto& i : el.second) {
            may_contain_allerg.insert(i);
        }
    }

    ansA = count_if(all_ingredients.begin(), all_ingredients.end(),
                    [&](const string& i) { return may_contain_allerg.count(i) == 0; });
}

Result Aoc::Day21Solver::SolveA() const {
    return ansA;
}

Result Aoc::Day21Solver::SolveB() const {
    auto a2i = allerg_to_ingr;
    deque<string> allerg_queue;
    unordered_map<string, string> mapping;
    for (const auto& el : a2i) {
        if (el.second.size() == 1) {
            mapping[*el.second.begin()] = el.first;
        } else {
            allerg_queue.push_back(el.first);
        }
    }
    while (!allerg_queue.empty()) {
        auto cur = allerg_queue.front();
        allerg_queue.pop_front();
        auto set_copy = a2i[cur];
        for (const auto& el : set_copy) {
            if (mapping.count(el) != 0) {
                a2i[cur].erase(el);
            }
        }
        if (a2i[cur].size() == 1) {
            mapping[*a2i[cur].begin()] = cur;
        } else {
            allerg_queue.push_back(cur);
        }
    }

    vector<string> results;
    results.reserve(mapping.size());

    for (const auto& el: mapping) {
        results.push_back(el.first);
    }
    sort(results.begin(), results.end(),
         [&](const string& left, const string& right) { return mapping.at(left) < mapping.at(right); });

    ostringstream out;
    for (size_t i = 0; i < results.size(); i++) {
        if (i > 0) out << ',';
        out << results[i];
    }

    return out.str();
}
