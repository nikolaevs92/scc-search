#pragma once

#include <vector>
#include <set>

void SCGSearch(size_t nodesNumber, const std::vector<std::pair<size_t, size_t>>& edges, std::set<std::set<size_t>>& result);