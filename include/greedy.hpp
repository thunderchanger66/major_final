#pragma once

#include <vector>
#include <utility>

class greedy
{
public:
    greedy(const std::vector<std::pair<int, int>>& path, const std::vector<std::vector<int>>& dilategrid) :
        path(path), dilategrid(dilategrid) {}

private:
    std::vector<std::pair<int, int>> path;
    std::vector<std::vector<int>> dilategrid;
};