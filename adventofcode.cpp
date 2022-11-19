#include "aoc_suite.h"

#include <fstream>
#include <sstream>

using namespace std;
using Solution = Aoc::SolutionWrapper;


void TestDay1() {
    {
        istringstream inp("1721\n"
                          "979\n"
                          "366\n"
                          "299\n"
                          "675\n"
                          "1456\n");
        Solution::ForDay(Day::_01).Process(inp)
                .ExpectA(514'579).ExpectB(241'861'950);
    }
    {
        ifstream inp("inputs/01.txt");
        Solution::ForDay(Day::_01).Process(inp)
                .ExpectA(858'496).ExpectB(263'819'430)
                .PrintResults(cout);
    }
}

void TestDay2() {
    {
        istringstream inp("1-3 a: abcde\n"
                          "1-3 b: cdefg\n"
                          "2-9 c: ccccccccc\n");
        Solution::ForDay(Day::_02).Process(inp)
                .ExpectA(2).ExpectB(1);
    }
    {
        ifstream inp("inputs/02.txt");
        Solution::ForDay(Day::_02).Process(inp)
                .ExpectA(393).ExpectB(690)
                .PrintResults(cout);
    }
}

void TestDay3() {
    {
        istringstream inp("..##.......\n"
                          "#...#...#..\n"
                          ".#....#..#.\n"
                          "..#.#...#.#\n"
                          ".#...##..#.\n"
                          "..#.##.....\n"
                          ".#.#.#....#\n"
                          ".#........#\n"
                          "#.##...#...\n"
                          "#...##....#\n"
                          ".#..#...#.#\n");
        Solution::ForDay(Day::_03).Process(inp)
                .ExpectA(7).ExpectB(336);
    }
    {
        ifstream inp("inputs/03.txt");
        Solution::ForDay(Day::_03).Process(inp)
                .ExpectA(191).ExpectB(1'478'615'040)
                .PrintResults(cout);
    }
}

void TestDay4() {
    {
        istringstream inp("ecl:gry pid:860033327 eyr:2020 hcl:#fffffd\n"
                          "byr:1937 iyr:2017 cid:147 hgt:183cm\n"
                          "\n"
                          "iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884\n"
                          "hcl:#cfa07d byr:1929\n"
                          "\n"
                          "hcl:#ae17e1 iyr:2013\n"
                          "eyr:2024\n"
                          "ecl:brn pid:760753108 byr:1931\n"
                          "hgt:179cm\n"
                          "\n"
                          "hcl:#cfa07d eyr:2025 pid:166559648\n"
                          "iyr:2011 ecl:brn hgt:59in\n");
        Solution::ForDay(Day::_04).Process(inp)
                .ExpectA(2).ExpectB(2);
    }
    {
        ifstream inp("inputs/04.txt");
        Solution::ForDay(Day::_04).Process(inp)
                .ExpectA(170).ExpectB(103)
                .PrintResults(cout);
    }
}

void TestDay5() {
    {
        istringstream inp("BFFFBBFRRR\n"
                          "BFFFBBFRLR\n");
        Solution::ForDay(Day::_05).Process(inp)
                .ExpectA(567).ExpectB(566);
    }
    {
        ifstream inp("inputs/05.txt");
        Solution::ForDay(Day::_05).Process(inp)
                .ExpectA(930).ExpectB(515)
                .PrintResults(cout);
    }
}

void TestDay6() {
    {
        istringstream inp("abc\n"
                          "\n"
                          "a\n"
                          "b\n"
                          "c\n"
                          "\n"
                          "ab\n"
                          "ac\n"
                          "\n"
                          "a\n"
                          "a\n"
                          "a\n"
                          "a\n"
                          "\n"
                          "b\n"
                          "\n");
        Solution::ForDay(Day::_06).Process(inp)
                .ExpectA(11).ExpectB(6);
    }
    {
        ifstream inp("inputs/06.txt");
        Solution::ForDay(Day::_06).Process(inp)
                .ExpectA(6542).ExpectB(3299)
                .PrintResults(cout);
    }
}

void TestDay7() {
    {
        istringstream inp("light red bags contain 1 bright white bag, 2 muted yellow bags.\n"
                          "dark orange bags contain 3 bright white bags, 4 muted yellow bags.\n"
                          "bright white bags contain 1 shiny gold bag.\n"
                          "muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.\n"
                          "shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.\n"
                          "dark olive bags contain 3 faded blue bags, 4 dotted black bags.\n"
                          "vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.\n"
                          "faded blue bags contain no other bags.\n"
                          "dotted black bags contain no other bags.\n");
        Solution::ForDay(Day::_07).Process(inp)
                .ExpectA(4).ExpectB(32);
    }
    {
        ifstream inp("inputs/07.txt");
        Solution::ForDay(Day::_07).Process(inp)
                .ExpectA(233).ExpectB(421'550)
                .PrintResults(cout);
    }
}

void TestDay8() {
    {
        istringstream inp("nop +0\n"
                          "acc +1\n"
                          "jmp +4\n"
                          "acc +3\n"
                          "jmp -3\n"
                          "acc -99\n"
                          "acc +1\n"
                          "jmp -4\n"
                          "acc +6\n");
        Solution::ForDay(Day::_08).Process(inp)
                .ExpectA(5).ExpectB(8);
    }
    {
        ifstream inp("inputs/08.txt");
        Solution::ForDay(Day::_08).Process(inp)
                .ExpectA(1384).ExpectB(761)
                .PrintResults(cout);
    }
}

void TestDay9() {
    {
        istringstream inp("35\n"
                          "20\n"
                          "15\n"
                          "25\n"
                          "47\n"
                          "40\n"
                          "62\n"
                          "55\n"
                          "65\n"
                          "95\n"
                          "102\n"
                          "117\n"
                          "150\n"
                          "182\n"
                          "127\n"
                          "219\n"
                          "299\n"
                          "277\n"
                          "309\n"
                          "576\n");
        Solution::ForDay(Day::_09).Process(inp)
                .ExpectA(127).ExpectB(62);
    }
    {
        ifstream inp("inputs/09.txt");
        Solution::ForDay(Day::_09).Process(inp)
                .ExpectA(1'038'347'917).ExpectB(137'394'018)
                .PrintResults(cout);
    }
}

void TestDay10() {
    {
        istringstream inp("16\n"
                          "10\n"
                          "15\n"
                          "5\n"
                          "1\n"
                          "11\n"
                          "7\n"
                          "19\n"
                          "6\n"
                          "12\n"
                          "4\n");
        Solution::ForDay(Day::_10).Process(inp)
                .ExpectA(35).ExpectB(8);
    }
    {
        istringstream inp("28\n"
                          "33\n"
                          "18\n"
                          "42\n"
                          "31\n"
                          "14\n"
                          "46\n"
                          "20\n"
                          "48\n"
                          "47\n"
                          "24\n"
                          "23\n"
                          "49\n"
                          "45\n"
                          "19\n"
                          "38\n"
                          "39\n"
                          "11\n"
                          "1\n"
                          "32\n"
                          "25\n"
                          "35\n"
                          "8\n"
                          "17\n"
                          "7\n"
                          "9\n"
                          "4\n"
                          "2\n"
                          "34\n"
                          "10\n"
                          "3\n");
        Solution::ForDay(Day::_10).Process(inp)
                .ExpectA(220).ExpectB(19208);
    }
    {
        ifstream inp("inputs/10.txt");
        Solution::ForDay(Day::_10).Process(inp)
                .ExpectA(2070).ExpectB(24'179'327'893'504)
                .PrintResults(cout);
    }
}

void TestDay11() {
    {
        istringstream inp("L.LL.LL.LL\n"
                          "LLLLLLL.LL\n"
                          "L.L.L..L..\n"
                          "LLLL.LL.LL\n"
                          "L.LL.LL.LL\n"
                          "L.LLLLL.LL\n"
                          "..L.L.....\n"
                          "LLLLLLLLLL\n"
                          "L.LLLLLL.L\n"
                          "L.LLLLL.LL\n");
        Solution::ForDay(Day::_11).Process(inp)
                .ExpectA(37).ExpectB(26);
    }
    {
        ifstream inp("inputs/11.txt");
        Solution::ForDay(Day::_11).Process(inp)
                .ExpectA(2310).ExpectB(2074)
                .PrintResults(cout);
    }
}

void TestDay12() {
    {
        istringstream inp("F10\n"
                          "N3\n"
                          "F7\n"
                          "R90\n"
                          "F11\n");
        Solution::ForDay(Day::_12).Process(inp)
                .ExpectA(25.0).ExpectB(286.0);
    }
    {
        ifstream inp("inputs/12.txt");
        Solution::ForDay(Day::_12).Process(inp)
                .ExpectA(1482.0).ExpectB(48739.0)
                .PrintResults(cout);
    }
}

void TestDay13() {
    {
        istringstream inp("939\n"
                          "7,13,x,x,59,x,31,19\n");
        Solution::ForDay(Day::_13).Process(inp)
                .ExpectA(295).ExpectB(1'068'781);
    }
    {
        ifstream inp("inputs/13.txt");
        Solution::ForDay(Day::_13).Process(inp)
                .ExpectA(4207).ExpectB(725'850'285'300'475)
                .PrintResults(cout);
    }
}

void TestDay14() {
    {
        istringstream inp("mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X\n"
                          "mem[8] = 11\n"
                          "mem[7] = 101\n"
                          "mem[8] = 0\n");
        Solution::ForDay(Day::_14).Process(inp)
                .ExpectA(165);
    }
    {
        istringstream inp("mask = 000000000000000000000000000000X1001X\n"
                          "mem[42] = 100\n"
                          "mask = 00000000000000000000000000000000X0XX\n"
                          "mem[26] = 1\n");
        Solution::ForDay(Day::_14).Process(inp)
                .ExpectB(208);
    }
    {
        ifstream inp("inputs/14.txt");
        Solution::ForDay(Day::_14).Process(inp)
                .ExpectA(14'925'946'402'938).ExpectB(3'706'820'676'200)
                .PrintResults(cout);
    }
}

void TestDay15() {
    {
        istringstream inp("0,3,6\n");
        Solution::ForDay(Day::_15).Process(inp)
                .ExpectA(436).ExpectB(175'594);
    }
    {
        ifstream inp("inputs/15.txt");
        Solution::ForDay(Day::_15).Process(inp)
                .ExpectA(758).ExpectB(814)
                .PrintResults(cout);
    }
}

void TestDay16() {
    {
        istringstream inp("class: 1-3 or 5-7\n"
                          "row: 6-11 or 33-44\n"
                          "seat: 13-40 or 45-50\n"
                          "\n"
                          "your ticket:\n"
                          "7,1,14\n"
                          "\n"
                          "nearby tickets:\n"
                          "7,3,47\n"
                          "40,4,50\n"
                          "55,2,20\n"
                          "38,6,12\n");
        Solution::ForDay(Day::_16).Process(inp)
                .ExpectA(71);
    }
    {
        ifstream inp("inputs/16.txt");
        Solution::ForDay(Day::_16).Process(inp)
                .ExpectA(28884).ExpectB(1'001'849'322'119)
                .PrintResults(cout);
    }
}

void TestDay17() {
    {
        istringstream inp(".#.\n"
                          "..#\n"
                          "###\n");
        Solution::ForDay(Day::_17).Process(inp)
                .ExpectA(112).ExpectB(848);
    }
    {
        ifstream inp("inputs/17.txt");
        Solution::ForDay(Day::_17).Process(inp)
                .ExpectA(424).ExpectB(2460)
                .PrintResults(cout);
    }
}

 void TestDay18() {
    {
        istringstream inp("2 * 3 + (4 * 5)\n"
                          "5 + (8 * 3 + 9 + 3 * 4 * 3)\n"
                          "5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))\n"
                          "((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2\n");
        Solution::ForDay(Day::_18).Process(inp)
                .ExpectA(26 + 437 + 12240 + 13632).ExpectB(46 + 1445 + 669060 + 23340);
    }
    {
        ifstream inp("inputs/18.txt");
        Solution::ForDay(Day::_18).Process(inp)
                .ExpectA(131'076'645'626).ExpectB(109'418'509'151'782)
                .PrintResults(cout);
    }
}

void TestDay19() {
    {
        istringstream inp("42: 9 14 | 10 1\n"
                          "9: 14 27 | 1 26\n"
                          "10: 23 14 | 28 1\n"
                          "1: \"a\"\n"
                          "11: 42 31\n"
                          "5: 1 14 | 15 1\n"
                          "19: 14 1 | 14 14\n"
                          "12: 24 14 | 19 1\n"
                          "16: 15 1 | 14 14\n"
                          "31: 14 17 | 1 13\n"
                          "6: 14 14 | 1 14\n"
                          "2: 1 24 | 14 4\n"
                          "0: 8 11\n"
                          "13: 14 3 | 1 12\n"
                          "15: 1 | 14\n"
                          "17: 14 2 | 1 7\n"
                          "23: 25 1 | 22 14\n"
                          "28: 16 1\n"
                          "4: 1 1\n"
                          "20: 14 14 | 1 15\n"
                          "3: 5 14 | 16 1\n"
                          "27: 1 6 | 14 18\n"
                          "14: \"b\"\n"
                          "21: 14 1 | 1 14\n"
                          "25: 1 1 | 1 14\n"
                          "22: 14 14\n"
                          "8: 42\n"
                          "26: 14 22 | 1 20\n"
                          "18: 15 15\n"
                          "7: 14 5 | 1 21\n"
                          "24: 14 1\n"
                          "\n"
                          "abbbbbabbbaaaababbaabbbbabababbbabbbbbbabaaaa\n"
                          "bbabbbbaabaabba\n"
                          "babbbbaabbbbbabbbbbbaabaaabaaa\n"
                          "aaabbbbbbaaaabaababaabababbabaaabbababababaaa\n"
                          "bbbbbbbaaaabbbbaaabbabaaa\n"
                          "bbbababbbbaaaaaaaabbababaaababaabab\n"
                          "ababaaaaaabaaab\n"
                          "ababaaaaabbbaba\n"
                          "baabbaaaabbaaaababbaababb\n"
                          "abbbbabbbbaaaababbbbbbaaaababb\n"
                          "aaaaabbaabaaaaababaa\n"
                          "aaaabbaaaabbaaa\n"
                          "aaaabbaabbaaaaaaabbbabbbaaabbaabaaa\n"
                          "babaaabbbaaabaababbaabababaaab\n"
                          "aabbbbbaabbbaaaaaabbbbbababaaaaabbaaabba\n");
        Solution::ForDay(Day::_19).Process(inp)
                .ExpectA(3).ExpectB(12);
    }
    {
        ifstream inp("inputs/19.txt");
        Solution::ForDay(Day::_19).Process(inp)
                .ExpectA(180).ExpectB(323)
                .PrintResults(cout);
    }
}

void TestDay20() {
    {
        ifstream inp("inputs/test20.txt");
        Solution::ForDay(Day::_20).Process(inp)
                .ExpectA(20'899'048'083'289).ExpectB(273);
    }
    {
        ifstream inp("inputs/20.txt");
        Solution::ForDay(Day::_20).Process(inp)
                .ExpectA(79'412'832'860'579).ExpectB(2155)
                .PrintResults(cout);
    }
}


void TestDay21() {
    {
        istringstream inp("mxmxvkd kfcds sqjhc nhms (contains dairy, fish)\n"
                          "trh fvjkl sbzzf mxmxvkd (contains dairy)\n"
                          "sqjhc fvjkl (contains soy)\n"
                          "sqjhc mxmxvkd sbzzf (contains fish)\n");
        Solution::ForDay(Day::_21).Process(inp)
                .ExpectA(5).ExpectB("mxmxvkd,sqjhc,fvjkl");
    }
    {
        ifstream inp("inputs/21.txt");
        Solution::ForDay(Day::_21).Process(inp)
                .ExpectA(2798).ExpectB("gbt,rpj,vdxb,dtb,bqmhk,vqzbq,zqjm,nhjrzzj")
                .PrintResults(cout);
    }
}


void TestDay22() {
    {
        istringstream inp("Player 1:\n"
                          "9\n"
                          "2\n"
                          "6\n"
                          "3\n"
                          "1\n"
                          "\n"
                          "Player 2:\n"
                          "5\n"
                          "8\n"
                          "4\n"
                          "7\n"
                          "10\n");
        Solution::ForDay(Day::_22).Process(inp)
                .ExpectA(306).ExpectB(291);
    }
    {
        ifstream inp("inputs/22.txt");
        Solution::ForDay(Day::_22).Process(inp)
                .ExpectA(30197).ExpectB(34031)
                .PrintResults(cout);
    }
}


void TestDay23() {
    {
        istringstream inp("389125467\n");
        Solution::ForDay(Day::_23).Process(inp)
                .ExpectA("67384529").ExpectB(149'245'887'792);
    }
    {
        ifstream inp("inputs/23.txt");
        Solution::ForDay(Day::_23).Process(inp)
                .ExpectA("95648732").ExpectB(192'515'314'252)
                .PrintResults(cout);
    }
}


void TestDay24() {
    {
        istringstream inp("sesenwnenenewseeswwswswwnenewsewsw\n"
                          "neeenesenwnwwswnenewnwwsewnenwseswesw\n"
                          "seswneswswsenwwnwse\n"
                          "nwnwneseeswswnenewneswwnewseswneseene\n"
                          "swweswneswnenwsewnwneneseenw\n"
                          "eesenwseswswnenwswnwnwsewwnwsene\n"
                          "sewnenenenesenwsewnenwwwse\n"
                          "wenwwweseeeweswwwnwwe\n"
                          "wsweesenenewnwwnwsenewsenwwsesesenwne\n"
                          "neeswseenwwswnwswswnw\n"
                          "nenwswwsewswnenenewsenwsenwnesesenew\n"
                          "enewnwewneswsewnwswenweswnenwsenwsw\n"
                          "sweneswneswneneenwnewenewwneswswnese\n"
                          "swwesenesewenwneswnwwneseswwne\n"
                          "enesenwswwswneneswsenwnewswseenwsese\n"
                          "wnwnesenesenenwwnenwsewesewsesesew\n"
                          "nenewswnwewswnenesenwnesewesw\n"
                          "eneswnwswnwsenenwnwnwwseeswneewsenese\n"
                          "neswnwewnwnwseenwseesewsenwsweewe\n"
                          "wseweeenwnesenwwwswnew\n");
        Solution::ForDay(Day::_24).Process(inp)
                .ExpectA(10).ExpectB(2208);
    }
    {
        ifstream inp("inputs/24.txt");
        Solution::ForDay(Day::_24).Process(inp)
                .ExpectA(351).ExpectB(3869)
                .PrintResults(cout);
    }
}


void TestDay25() {
    {
        istringstream inp("5764801\n"
                          "17807724\n");
        Solution::ForDay(Day::_25).Process(inp)
                .ExpectA(14'897'079);
    }
    {
        ifstream inp("inputs/25.txt");
        Solution::ForDay(Day::_25).Process(inp)
                .ExpectA(12'227'206)
                .PrintResults(cout);
    }
}


int main() {
    TestDay1();
    TestDay2();
    TestDay3();
    TestDay4();
    TestDay5();
    TestDay6();
    TestDay7();
    TestDay8();
    TestDay9();
    TestDay10();
    TestDay11();
    TestDay12();
    TestDay13();
    TestDay14();
    TestDay15();
    TestDay16();
    TestDay17();
    TestDay18();
    TestDay19();
    TestDay20();
    TestDay21();
    TestDay22();
    TestDay23();
    TestDay24();
    TestDay25();

    return 0;
}
