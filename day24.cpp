#include "adventofcode.h"

#include <map>
#include <sstream>

using namespace std;

Aoc::Day24Solver::Tile Aoc::Day24Solver::Tile::operator + (const Tile& other) const {
    return {x + other.x, y + other.y};
}
bool Aoc::Day24Solver::Tile::operator == (const Tile& other) const {
    return tie(x, y) == tie(other.x, other.y);
}
size_t Aoc::Day24Solver::TileHasher::operator()(const Tile& t) const {
    return hasher(t.x) * 999773 + hasher(t.y);
}

void Aoc::Day24Solver::ProcessInput(istream& in) {
    unordered_map<Tile, int, TileHasher> tiles_seen;
    string s;
    while (getline(in, s)) {
        Tile tile {0, 0};
        for (size_t i = 0; i < s.size(); i++) {
            int choice = abs(tile.y) % 2;
            string dir; dir.push_back(s[i]);
            if (MAPPING[choice].count(dir) == 0) {
                dir.push_back(s[++i]);
            }
            tile = tile + MAPPING[choice].at(dir);
        }
        tiles_seen[tile]++;
    }

    for (const auto& el : tiles_seen) {
        if (el.second % 2 == 1) black_tiles.push_back(el.first);
    }
}

Result Aoc::Day24Solver::SolveA() const {
    return (int64_t) black_tiles.size();
}

Result Aoc::Day24Solver::SolveB() const {
    TileSet current {black_tiles.begin(), black_tiles.end()};
    for (int i = 0; i < 100; i++) {
        FlipTiles(current);
    }
    return (int64_t) current.size();
}

void Aoc::Day24Solver::FlipTiles(TileSet& current) {
    TileSet current_copy = current, to_visit = current;
    for (const auto& el : current) {
        for (const auto& dxdy : MAPPING[abs(el.y) % 2]) {
            auto tmp = el + dxdy.second;
            to_visit.insert(tmp);
        }
    }

    for (const auto& cur : to_visit) {
        int cnt = CountBlackTiles(current, cur);
        if (current.count(cur) == 0) {
            if (cnt == 2) current_copy.insert(cur);
        } else {
            if (cnt == 0 || cnt > 2) current_copy.erase(cur);
        }
    }

    current = std::move(current_copy);
}

int Aoc::Day24Solver::CountBlackTiles(const TileSet& current, Tile tile) {
    const auto& m = MAPPING[abs(tile.y) % 2];
    return count_if(m.begin(), m.end(), [&](const auto& p) { return current.count(tile + p.second) != 0; });
}

const vector<unordered_map<string, Aoc::Day24Solver::Tile>> Aoc::Day24Solver::MAPPING = {
        {
            {"e", {1, 0}}, {"w", {-1, 0}},
            {"ne", {0, 1}}, {"nw", {-1, 1}},
            {"se", {0, -1}}, {"sw", {-1, -1}}
        },
        {
            {"e", {1, 0}}, {"w", {-1, 0}},
            {"ne", {1, 1}}, {"nw", {0, 1}},
            {"se", {1, -1}}, {"sw", {0, -1}}
        }
};
