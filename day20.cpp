#include "adventofcode.h"

#include <cmath>
#include <sstream>

using namespace std;


void Aoc::Day20Solver::ProcessInput(istream& in) {
    string s;
    int id;
    vector<string> data;
    while (getline(in, s)) {
        if (s.empty()) {
           tiles[id] = Tile{id, std::move(data)};
           data = {};
        } else if (s[0] == 'T') {
            id = stoi(s.substr(5));
        } else {
            data.push_back(std::move(s));
        }
    }

    for (const auto& t1 : tiles) {
        for (const auto& t2 : tiles) {
            if (t1.first == t2.first) continue;
            auto match = TilesMatch(t1.second, t2.second);
            if (match) {
                matches[t1.second.GetId()].insert(t2.second.GetId());
            }
        }
    }
}

Result Aoc::Day20Solver::SolveA() const {
    int64_t result = 1;
    for (const auto& el : matches) {
        if (el.second.size() == 2) result *= el.first;
    }
    return result;
}

Result Aoc::Day20Solver::SolveB() const {
    auto match_top_bottom = [](const Tile& top, const Tile& bottom) { return top.GetBottom() == bottom.GetTop(); };
    auto match_left_right = [](const Tile& left, const Tile& right) { return left.GetRight() == right.GetLeft(); };

    // pick top left tile and rotate/flip it if needed
    auto it = find_if(matches.begin(), matches.end(), [](const auto& el) { return el.second.size() == 2; });
    auto grid_sz = (size_t) sqrt(tiles.size());
    vector<vector<int>> whole (grid_sz, vector<int>(grid_sz, -1));
    whole[0][0] = it->first;
    {
        for (size_t i = 0; i < 8; i++) {
            if (i == 4) tiles[it->first].Reverse();
            if (MaybeAlignTiles(it->first, *(it->second.begin()), match_top_bottom)
                && MaybeAlignTiles(it->first, *(next(it->second.begin())), match_left_right))
                break;
            tiles[it->first].Rotate90();
        }
    }

    // add remaining tiles to the image
    unordered_set<int> seen {whole[0][0]};

    auto matches_copy = matches;
    for (size_t i = 1; i < whole.size(); i++) {
        auto& candidates = matches_copy[whole[i-1][0]];
        for (auto candidate : candidates) {
            if (seen.count(candidate) != 0) continue;
            auto res = MaybeAlignTiles(whole[i-1][0], candidate, match_top_bottom);
            if (res) {
                whole[i][0] = candidate;
                seen.insert(candidate);
                break;
            }
        }
        candidates.erase(whole[i][0]);
    }
    for (size_t i = 0; i < whole.size(); i++) {
        for (size_t j = 1; j < whole[0].size(); j++) {
            auto& candidates = matches_copy[whole[i][j-1]];
            for (auto candidate : candidates) {
                if (seen.count(candidate) != 0) continue;
                auto res = MaybeAlignTiles(whole[i][j-1], candidate, match_left_right);
                if (res) {
                    whole[i][j] = candidate;
                    seen.insert(candidate);
                    break;
                }
            }
            candidates.erase(whole[i][j]);
        }
    }

    // construct full image
    ostringstream out;
    auto sz = tiles.begin()->second.GetSize();
    for (size_t i = 0; i < whole.size(); i++) {
        for (size_t row = 1; row + 1 < sz; row++) {
            for (size_t j = 0; j < whole[0].size(); j++) {
                const auto& q = tiles[whole[i][j]].GetRow(row);
                out << q.substr(1, q.size() - 2);
            }
            out << '\n';
        }
    }
    string whole_tile = out.str(), s;
    istringstream tile_stream(whole_tile);
    vector<string> data_;
    while (getline(tile_stream, s)) {
        data_.push_back(std::move(s));
    }
    Tile photo {-1, std::move(data_)};

    // find monsters
    for (size_t i = 0; i < 8; i++) {
        if (i == 4) photo.Reverse();
        int cnt = photo.FindMonsters(sea_monster);
        if (cnt > 0) break;
        photo.Rotate90();
    }

    return photo.GetRoughness();
}

Aoc::Day20Solver::Tile::Tile(int i, vector<string> tile) : id(i), data(std::move(tile)) {}

int Aoc::Day20Solver::Tile::GetId() const { return id;}
size_t Aoc::Day20Solver::Tile::GetSize() const { return data.size(); }
const string& Aoc::Day20Solver::Tile::GetRow(size_t row) { return data[row]; }
string Aoc::Day20Solver::Tile::GetTop() const { return data.front(); }
string Aoc::Day20Solver::Tile::GetBottom() const { return data.back(); }
string Aoc::Day20Solver::Tile::GetLeft() const {
    string res;
    for (const auto& row : data) res.push_back(row.front());
    return res;
}
string Aoc::Day20Solver::Tile::GetRight() const {
    string res;
    for (const auto& row : data) res.push_back(row.back());
    return res;
}

vector<string> Aoc::Day20Solver::Tile::GetSides() const {
    return {GetLeft(), GetTop(), GetRight(), GetBottom()};
}

void Aoc::Day20Solver::Tile::Rotate90() {
    vector<string> data_copy(data[0].size(), string(data.size(), ' '));
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = 0; j < data[0].size(); j++) {
            data_copy[j][data.size() - i - 1] = data[i][j];
        }
    }
    data = std::move(data_copy);
}

void Aoc::Day20Solver::Tile::Reverse() {
    reverse(data.begin(), data.end());
}

bool Aoc::Day20Solver::TilesMatch(const Tile& t1, const Tile& t2) {
    for (const auto& s1 : t1.GetSides()) {
        for (const auto& s2 : t2.GetSides()) {
            string reversed {s2.rbegin(), s2.rend()};
            if (s1 == s2 || s1 == reversed) return true;
        }
    }
    return false;
}

Aoc::Day20Solver::Monster::Monster(vector<string> im) : image(std::move(im)) {
    size_x = image.size(); size_y = image[0].size();
    for (size_t i = 0; i < image.size(); i++) {
        for (size_t j = 0; j < image[i].size(); j++) {
            if (image[i][j] == '#')
                points.emplace_back(i, j);
        }
    }
}

bool Aoc::Day20Solver::MaybeAlignTiles(int ref_id, int cur_id,
                                       const function<bool(const Tile&, const Tile&)>& check) const {
    auto& ref = tiles[ref_id];
    auto& cur = tiles[cur_id];
    for (auto i = 0; i < 8; i++) {
        if (i == 4) cur.Reverse();
        if (check(ref, cur)) return true;
        cur.Rotate90();
    }
    return false;
}

int Aoc::Day20Solver::Tile::GetRoughness() const {
    int res = 0;
    for (const auto& row : data) {
        res += count(row.begin(), row.end(), '#');
    }
    return res;
}

int Aoc::Day20Solver::Tile::FindMonsters(const Monster& monster) {
    int res = 0;

    for (size_t i = 0; i + monster.size_x < data.size(); i++) {
        for (size_t j = 0; j + monster.size_y < data[0].size(); j++) {
            bool found = all_of(monster.points.begin(), monster.points.end(),
                                [&](const auto& xy) { return data[i + xy.first][j + xy.second] == '#'; });
            if (found) {
                res += 1;
                for_each(monster.points.begin(), monster.points.end(),
                         [&](const auto& xy) { data[i + xy.first][j + xy.second] = 'O'; });
            }
        }
    }

    return res;
}
