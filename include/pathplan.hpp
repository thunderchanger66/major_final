#pragma once

#include "imgprocess.hpp"
#include <vector>

class PathPlanner: public ImageProcessor
{
private:
    std::vector<std::vector<bool>> visited; // 访问标记
    std::vector<std::pair<int, int>> path; // 存储路径点
public:
    PathPlanner();
    void zigzagSweep();
};