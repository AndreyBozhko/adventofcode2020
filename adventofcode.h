#pragma once

#include "bootcode.h"
#include "utils.h"

#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>


namespace Aoc {

    class Solver {
    public:
        explicit Solver(Day day) : day_(day) {}
        virtual ~Solver() = default;

        virtual void ProcessInput(std::istream& in) = 0;

        [[nodiscard]] virtual Day GetDay() const { return day_; }
        [[nodiscard]] virtual Result SolveA() const = 0;
        [[nodiscard]] virtual Result SolveB() const = 0;
    private:
        Day day_;
    };


    class Day1Solver final : public Solver {
    public:
        Day1Solver() : Solver(Day::_01) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;
    private:
        std::vector<int> numbers;
        const int TARGET = 2020;
    };


    class Day2Solver final : public Solver {
    public:
        Day2Solver() : Solver(Day::_02) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;
    private:
        int validA = 0, validB = 0;
    };


    class Day3Solver final : public Solver {
    public:
        Day3Solver() : Solver(Day::_03) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;
    private:
        std::vector<std::string> tree_map;
        [[nodiscard]] int CountTreesForSlope(int slope_x, int slope_y) const;
        const std::vector<std::pair<int, int>> slopes {
                {1,1}, {3,1}, {5,1}, {7,1}, {1,2}
        };
    };


    class Day4Solver final : public Solver {
    public:
        Day4Solver() : Solver(Day::_04) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;
    private:
        int countA = 0, countB = 0;
        static bool CheckIfPresent(const std::unordered_map<std::string, std::string>& data);
        static bool CheckIfValid(const std::unordered_map<std::string, std::string>& data);
    };


    class Day5Solver final : public Solver {
    public:
        Day5Solver() : Solver(Day::_05) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;
    private:
        int maxId = 0, actualId = 0;
        std::vector<int> ids;
        static std::pair<int, int> ParseSeat(const std::string& s);
    };


    class Day6Solver final : public Solver {
    public:
        Day6Solver() : Solver(Day::_06) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;
    private:
        int countA = 0, countB = 0;
    };


    class Day7Solver final : public Solver {
    public:
        Day7Solver() : Solver(Day::_07) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;
    private:
        const std::string MY_BAG = "shiny gold";
        std::unordered_map<std::string, std::unordered_map<std::string, int>> mapping;
        std::unordered_map<std::string, std::unordered_set<std::string>> inverted_mapping;
        int CountInside(const std::string& bag) const;
    };


    class Day8Solver final : public Solver {
    public:
        Day8Solver() : Solver(Day::_08) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;
    private:
        std::vector<BootCode::Instruction> instr;
        static const std::unordered_map<BootCode::Op, BootCode::Op> SWITCH_MATRIX;
    };


    class Day9Solver final : public Solver {
    public:
        Day9Solver() : Solver(Day::_09) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;
    private:
        int preamble = -1, weaknessA = -1, weaknessB = -1;
        std::vector<int> sequence;

        static int FindWeaknessA(const std::vector<int>& seq, int preamble);
        static int FindWeaknessB(const std::vector<int>& seq, int target);
    };


    class Day10Solver final : public Solver {
    public:
        Day10Solver() : Solver(Day::_10) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;
    private:
        std::vector<int> sequence;
    };


    class Day11Solver final : public Solver {
    public:
        Day11Solver() : Solver(Day::_11) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;

        enum class Seat : char {
            FLOOR = '.', EMPTY = 'L', TAKEN = '#'
        };
    private:
        std::vector<std::vector<Seat>> seats;

        static int CountNeighbors(const std::vector<std::vector<Seat>>& seats,
                                  size_t i, size_t j, const std::set<Seat>& continue_on);
        static int Simulate(std::vector<std::vector<Seat>> seats,
                            const std::set<Seat>& continue_on, int max_tolerance);

        static const std::vector<std::pair<int, int>> DXDY;
    };


    class Day12Solver final : public Solver {
    public:
        Day12Solver() : Solver(Day::_12) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;

        struct Step {
            char action;
            int value;
        };
        struct Position {
            double x, y;
        };
    private:
        std::vector<Step> instructions;
    };


    class Day13Solver final : public Solver {
    public:
        Day13Solver() : Solver(Day::_13) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;
    private:
        int ts = 0;
        std::vector<std::optional<int>> bus_ids;
    };


    class Day14Solver final : public Solver {
    public:
        Day14Solver() : Solver(Day::_14) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;

        struct Address {
            int64_t value;
        };
        struct Value {
            int64_t value;
        };
        struct MemoryAccess {
            Address addr;
            Value value;
        };
        struct Mask {
            std::string value;

            std::vector<uint64_t> operator() (const Address& addr) const;
            uint64_t operator() (const Value& val) const;
        };
    private:
        std::vector<std::variant<Mask, MemoryAccess>> instructions;
    };


    class Day15Solver final : public Solver {
    public:
        Day15Solver() : Solver(Day::_15) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;

        struct HeapOfTwo {
            int64_t first = -1, last = -1;
            int sz = 0;

            void Push(int64_t num);
        };
    private:
        std::vector<int64_t> sequence;

        static int64_t SolveFor(const std::vector<int64_t>& seq, int64_t pos);
    };


    class Day16Solver final : public Solver {
    public:
        Day16Solver() : Solver(Day::_16) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;

        struct Rule {
            std::string field;
            int a, b, c, d;

            bool operator() (int x) const;
        };
        using Ticket = std::vector<int>;
    private:
        int ansA = 0;
        std::vector<Rule> rules;
        std::vector<Ticket> tickets;

        [[nodiscard]] std::vector<int> IsInvalid(const Ticket& ticket) const;
    };


    class Day17Solver final : public Solver {
    public:
        Day17Solver() : Solver(Day::_17) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;

        struct Point {
            int x, y, z, t;

            bool operator== (const Point& other) const;
            Point operator+ (const Point& other) const;
        };

        struct PointHasher {
            std::hash<int> hasher;

            size_t operator() (const Point& pt) const;
        };

        enum class Action {
            NONE, INSERT, DELETE
        };
    private:
        using PointSet = std::unordered_set<Point, PointHasher>;
        PointSet grid;

        static void RunCycle(PointSet& active, const std::vector<Point>& deltas);
        static Action ShouldChangeState(Point pt, const PointSet& active, const std::vector<Point>& deltas);

        static constexpr Point ZERO = Point{0, 0, 0, 0};
        static const std::vector<Point> DXDYDZ, DXDYDZDT;
    };


    class Day18Solver final : public Solver {
    public:
        Day18Solver() : Solver(Day::_18) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;

        using Number = int64_t;
        enum class Op : char { ADD = '+', MULTIPLY = '*' };
        enum class Bracket : char { LEFT = '(', RIGHT = ')' };

    private:
        using Expression = std::vector<std::variant<Number, Op, Bracket>>;
        using Iterator = Expression::const_iterator;

        std::vector<Expression> expressions;
        static Number EvaluateLeftToRight(Iterator left, Iterator right);
        static Number EvaluateAddFirst(Iterator left, Iterator right);
        static Iterator FindMatchingClosingBracket(Iterator left);
    };


    class Day19Solver final : public Solver {
    public:
        Day19Solver() : Solver(Day::_19) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;

        class Rule {
        public:
            [[nodiscard]] virtual std::optional<size_t> Match(const std::string& s, size_t start) const = 0;
            [[nodiscard]] virtual size_t GetSize() const = 0;
            virtual ~Rule() = default;
        };

        class CharRule : public Rule {
        public:
            explicit CharRule(char c) : ch(c) {}
            [[nodiscard]] std::optional<size_t> Match(const std::string &s, size_t start) const override;
            [[nodiscard]] size_t GetSize() const override;
        private:
            char ch;
        };

        class SeqRule : public Rule {
        public:
            SeqRule(const std::unordered_map<int, std::unique_ptr<Rule>>& refs, const std::string& s);
            [[nodiscard]] std::optional<size_t> Match(const std::string &s, size_t pos) const override;
            [[nodiscard]] size_t GetSize() const override;

        private:
            const std::unordered_map<int, std::unique_ptr<Rule>>& references;
            std::vector<int> rule_idx;
        };

        class OrRule : public Rule {
        public:
            OrRule(std::unique_ptr<Rule> l, std::unique_ptr<Rule> r)
                : left(std::move(l)), right(std::move(r)) {}
            [[nodiscard]] std::optional<size_t> Match(const std::string &s, size_t start) const override;
            [[nodiscard]] size_t GetSize() const override;
        private:
            std::unique_ptr<Rule> left, right;
        };

    private:
        std::unordered_map<int, std::unique_ptr<Rule>> rules;
        std::vector<std::string> messages;
    };


    class Day20Solver final : public Solver {
    public:
        Day20Solver() : Solver(Day::_20) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;

        struct Monster {
            explicit Monster(std::vector<std::string> im);
            std::vector<std::string> image;
            size_t size_x, size_y;
            std::vector<std::pair<size_t, size_t>> points;
        };

        class Tile {
        public:
            Tile() = default;
            Tile(int i, std::vector<std::string> tile);
            [[nodiscard]] int GetId() const;
            [[nodiscard]] std::string GetTop() const;
            [[nodiscard]] std::string GetBottom() const;
            [[nodiscard]] std::string GetLeft() const;
            [[nodiscard]] std::string GetRight() const;
            [[nodiscard]] std::vector<std::string> GetSides() const;
            [[nodiscard]] size_t GetSize() const;
            [[nodiscard]] const std::string& GetRow(size_t row);
            void Rotate90();
            void Reverse();
            [[nodiscard]] int FindMonsters(const Monster& monster);
            [[nodiscard]] int GetRoughness() const;
        private:
            int id = -1;
            std::vector<std::string> data;
        };

    private:
        // const methods are allowed to rotate/flip tiles
        mutable std::unordered_map<int, Tile> tiles;
        std::unordered_map<int, std::unordered_set<int>> matches;

        const Monster sea_monster {{
            "                  # ",
            "#    ##    ##    ###",
            " #  #  #  #  #  #   "
        }};

        static bool TilesMatch(const Tile& t1, const Tile& t2);
        bool MaybeAlignTiles(int ref_id, int cur_id,
                             const std::function<bool(const Tile&, const Tile&)>& check) const;
    };


    class Day21Solver final : public Solver {
    public:
        Day21Solver() : Solver(Day::_21) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;
    private:
        int ansA = 0;
        std::unordered_map<std::string, std::set<std::string>> allerg_to_ingr;
    };


    class Day22Solver final : public Solver {
    public:
        Day22Solver() : Solver(Day::_22) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;

        enum class Player {
            FIRST, SECOND
        };
    private:
        std::deque<int> deck1, deck2;

        static Player Recurse(std::deque<int>& d1, std::deque<int>& d2);
        static std::string ComputeState(const std::deque<int>& d1, const std::deque<int>& d2);
        static int ComputeScore(const std::deque<int>& d);
    };


    class Day23Solver final : public Solver {
    public:
        Day23Solver() : Solver(Day::_23) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;
    private:
        using ListIterator = std::list<int>::const_iterator;
        std::list<int> original_cups;

        static void PlayGame(std::list<int>& cups, size_t rounds, int max_el);
    };


    class Day24Solver final : public Solver {
    public:
        Day24Solver() : Solver(Day::_24) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;

        struct Tile {
            int x, y;

            Tile operator + (const Tile& other) const;
            bool operator ==(const Tile& other) const;
        };

        struct TileHasher {
            std::hash<int> hasher;

            size_t operator() (const Tile& t) const;
        };
    private:
        using TileSet = std::unordered_set<Tile, TileHasher>;
        std::vector<Tile> black_tiles;

        static void FlipTiles(TileSet& current);
        static int CountBlackTiles(const TileSet& current, Tile tile);

        static const std::vector<std::unordered_map<std::string, Tile>> MAPPING;
    };


    class Day25Solver final : public Solver {
    public:
        Day25Solver() : Solver(Day::_25) {}
        void ProcessInput(std::istream& in) override;
        [[nodiscard]] Result SolveA() const override;
        [[nodiscard]] Result SolveB() const override;

        struct Device {
            int loop = 0;
            const int64_t subject = 7, modulus = 20201227;

            [[nodiscard]] int64_t GeneratePublicKey() const;
            [[nodiscard]] int64_t GenerateEncryptionKey(int64_t subject_number) const;
            static Device FromPublicKey(int64_t pubkey);
        };
    private:
        std::vector<Device> devices;
    };

}
