#pragma once

#include "imgprocess.hpp"
#include <vector>
#include <utility> // for std::pair

class PathPlanner: public ImageProcessor
{
private:
    int rows;
    int cols;

    std::vector<std::vector<bool>> visited; // 访问标记
    std::vector<std::pair<int, int>> path; // 存储路径点
public:
    PathPlanner();
    void zigzagSweep();//之字形进行全覆盖路径
    void showPath();//显示规划的路径
    void BFSLabel();//进行地图分区，分成区域
};