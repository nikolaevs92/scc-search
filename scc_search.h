#pragma once

#include <vector>
#include <set>

std::set<std::set<size_t>> SCGSearch(size_t nodesNumber, const std::vector<std::pair<size_t, size_t>>& edges);