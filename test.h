#pragma once

#include <iostream>
#include <vector>
#include <set>


struct SCGSearchTestData{
    size_t InputNodesNumber;
    std::vector<std::pair<size_t, size_t>> InputEdges;

    std::set<std::set<size_t>> CorrectOutput;
    SCGSearchTestData(size_t inputNodesNumber, const std::vector<std::pair<size_t, size_t>>& inputEdges, const std::set<std::set<size_t>>& correctOutput) :
        InputNodesNumber(inputNodesNumber), InputEdges(inputEdges), CorrectOutput(correctOutput) {}
};

bool TestOneSCGSearch(const SCGSearchTestData& testData);
void TestSCGSearch();