#include "adventofcode.h"

#include <cmath>

using namespace std;


Aoc::Day12Solver::Position operator + (Aoc::Day12Solver::Position left, Aoc::Day12Solver::Position right) {
    return {left.x + right.x, left.y + right.y};
}
Aoc::Day12Solver::Position operator * (Aoc::Day12Solver::Position left, double factor) {
    return {left.x * factor, left.y * factor};
}

double ManhattanDistance(Aoc::Day12Solver::Position left, Aoc::Day12Solver::Position right) {
    return abs(left.x - right.x) + abs(left.y - right.y);
}


void Aoc::Day12Solver::ProcessInput(istream& in) {
    char c; int v;
    while (in >> c >> v) {
        instructions.emplace_back(Step{c, v});
    }
}

Result Aoc::Day12Solver::SolveA() const {
    Position current {0, 0};
    double angle = 0.0;

    for (const auto& st : instructions) {
        if (st.action == 'N') { current.y += st.value; }
        else if (st.action == 'S') { current.y -= st.value; }
        else if (st.action == 'E') { current.x += st.value; }
        else if (st.action == 'W') { current.x -= st.value; }
        else if (st.action == 'L') { angle += st.value; }
        else if (st.action == 'R') { angle -= st.value; }
        else if (st.action == 'F') {
            double alpha = angle * M_PI / 180.0;
            current = current + Position{cos(alpha), sin(alpha)} * st.value;
        }
    }

    return ManhattanDistance(current, {0, 0});
}

Result Aoc::Day12Solver::SolveB() const {
    Position current {0, 0}, waypoint {10, 1};

    for (const auto& st : instructions) {
        if (st.action == 'N') { waypoint.y += st.value; }
        else if (st.action == 'S') { waypoint.y -= st.value; }
        else if (st.action == 'E') { waypoint.x += st.value; }
        else if (st.action == 'W') { waypoint.x -= st.value; }
        else if (st.action == 'L' || st.action == 'R') {
            double angle = st.value * M_PI / 180.0;
            angle = st.action == 'L' ? angle : -angle;
            waypoint = {waypoint.x * cos(angle) - waypoint.y * sin(angle),
                        waypoint.x * sin(angle) + waypoint.y * cos(angle)};
        } else if (st.action == 'F') {
            current = current + waypoint * st.value;
        }
    }

    return ManhattanDistance(current, {0, 0});
}
