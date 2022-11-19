#include "utils.h"

using namespace std;


ostream& operator << (ostream& out, const Day& day) {
    return out << "Day " << (static_cast<size_t>(day) + 1);
}

ostream& operator << (ostream& out, const Result& value) {
    visit([&](const auto& el) { out << el; }, value);
    return out;
}


bool operator == (const Result& value, int64_t v) {
    return holds_alternative<int64_t>(value) && v == get<int64_t>(value);
}
bool operator == (const Result& value, double v) {
    return holds_alternative<double>(value) && abs(v - get<double>(value)) < 1e-6;
}
bool operator == (const Result& value, const string& v) {
    return holds_alternative<string>(value) && v == get<string>(value);
}
bool operator == (const Result& left, const Result& right) {
    return visit([&](auto x) { return left == x; }, right);
}
