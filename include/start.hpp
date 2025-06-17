#pragma once

#include <vector>
#include <utility> // for std::pair

struct returnpath// 返回路径和网格数据的结构体，用于指标
{
    std::vector<std::pair<int, int>> path; // 存储路径点
    std::vector<std::vector<int>> grid; // 网格数据，0表示可通行，1表示不可通行
};

returnpath returnPath();