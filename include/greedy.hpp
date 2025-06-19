#pragma once

#include <vector>
#include <utility>
#include "astar.hpp"

class greedy : public Astar
{
public:
    greedy(const std::vector<std::pair<int, int>>& path, const std::vector<std::vector<int>>& dilategrid) :
        path(path), dilategrid(dilategrid){}

    std::vector<std::pair<int, int>> greedyPath();

private:
    std::vector<std::pair<int, int>> path;
    std::vector<std::vector<int>> dilategrid;

    std::vector<bool> pathVisitd;
    std::vector<std::pair<int, int>> greedypath;

    void calculatedistance();
    std::vector<std::vector<int>> distanceMatrix;
    int n;//原始路徑長度
};