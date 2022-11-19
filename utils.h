#pragma once

#include <iostream>
#include <variant>


enum class Day {
    _01, _02, _03, _04, _05,
    _06, _07, _08, _09, _10,
    _11, _12, _13, _14, _15,
    _16, _17, _18, _19, _20,
    _21, _22, _23, _24, _25
};

using Result = std::variant<int64_t, double, std::string>;

std::ostream& operator << (std::ostream& out, const Day& day);
std::ostream& operator << (std::ostream& out, const Result& value);


bool operator == (const Result& value, int64_t v);
bool operator == (const Result& value, double v);
bool operator == (const Result& value, const std::string& v);
bool operator == (const Result& left, const Result& right);
