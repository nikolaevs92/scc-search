#include <iostream>

#include "test.h"
#include "scc_search.h"


std::ostream& operator<<(std::ostream &out, const std::set<size_t>& set) {
    out  << "( ";
    for (const auto &item : set) {
        out << item << ' ';
    }
    return out  << ')' << std::endl;
}

std::ostream& operator<<(std::ostream &out, const std::set<std::set<size_t>>& setVector) {
    out  << "{";
    for (const auto &set : setVector) {
        out << '\t' << set << ',';
    }
    return out  << '}' << std::endl;
}

std::ostream& operator<<(std::ostream &out, const std::vector<std::pair<size_t, size_t>>& pairVector) {
    out  << "{";
    for (const auto &pair : pairVector) {
        out << "\t(" << pair.first << ' ' << pair.second << "), ";
    }
    return out  << '}' << std::endl;
}

bool operator==(std::set<std::set<size_t>>& left, std::set<std::set<size_t>>& right) {
    if (left.size() != right.size()) {
        return false;
    }

    auto leftIt = left.begin();
    auto rightIt = right.begin();

    while (leftIt != left.end() && rightIt != right.end()) {
        if (!((*leftIt) == (*rightIt))) {
            return false;
            ++leftIt;
            ++ rightIt;
        }
    }

    return true;
}

bool TestOneSCGSearch(const SCGSearchTestData& testData) {
    auto realOutput = SCGSearch(testData.InputNodesNumber, testData.InputEdges);
    if (realOutput == testData.CorrectOutput) {
        return true;
    }
    std::cout << "\nfaliled test with input: " << testData.InputNodesNumber << ' ' << testData.InputEdges << std::endl;
    std::cout << "correct output: " << testData.CorrectOutput << std::endl;
    std::cout << "real output: " << realOutput << std::endl;
    return false;
}

// TODO: add some test for catch errors
void TestSCGSearch() {
    std::cout << "start tests" << std::endl;
    const std::vector<SCGSearchTestData> tests{
            {0, {}, {}},
            {1, {}, {{0}}},
            {1, {{0,0}}, {{0}}},
            {1, {{0,0},{0,0}}, {{0}}},
            {2, {}, {{0}, {1}}},
            {2, {{0,0}, {0,1}, {0,0}, {1,1}}, {{0}, {1}}},
            {2, {{0,1}, {1,0}, {0,0}}, {{0,1}}},
            {8, {{0,1}, {1,2}, {2,3}, {3,0}, {2,4}, {4,5}, {5,6}, {6,4}, {5,7}}, {{0,1,2,3}, {4,5,6}, {7}}},
            {4, {{0,2}, {1,0}, {3,0}, {1,3}}, {{0}, {1}, {2}, {3}}},
            {5, {{0,1}, {1,2}, {2,3}, {3,1}, {4,3}, {0,4}}, {{0}, {1,2,3}, {4}}},
            {8, {{0,1}, {1,2}, {2,0}, {3,4}, {4,3}, {5,6}, {6,5}, {6,7}, {7,6}, {2,3}, {1,3}, {1,5}, {7,4}, {5,4}}, {{0,1,2}, {3,4}, {5,6,7}}}
        };
    int correctCounter = 0;
    for (const auto& test : tests) {
        correctCounter += TestOneSCGSearch(test);
    }
    std::cout << correctCounter << " test correct of " << tests.size() << std::endl;
    std::cout << "end tests" << std::endl;
}
