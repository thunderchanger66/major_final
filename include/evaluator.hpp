#pragma once

#include <vector>
#include <utility> // for std::pair
#include <opencv2/opencv.hpp> 

struct returnpath// 返回路径和网格数据的结构体，用于指标
{
    std::vector<std::pair<int, int>> path; // 存储路径点
    std::vector<std::vector<int>> grid; // 网格数据，0表示可通行，1表示不可通行
};

class Evaluator
{
public:
    Evaluator(const returnpath& rp) : returnPath(rp), 
    finalShow(cv::Size(rp.grid[0].size(), rp.grid.size()), CV_8UC3, cv::Scalar(255, 255, 255)),
    visitedCar(rp.grid.size(), std::vector<int>(rp.grid[0].size(), -1)) {}

    void beTheCar();// 变成车的大小，便于可视化实际情况并进行性能评估
    std::vector<std::vector<int>> visitedCar; // 访问标记，用于记录哪些点已经被访问过// -1表示不可访问，0表示可访问，1表示车经过

private:
    returnpath returnPath;// 存储返回的路径和网格数据
    cv::Mat finalShow;// 最终显示的图像
    int emptyCount = 0; // 统计可通行的点数
    int coveredCount = 0; // 统计覆盖的点数
};