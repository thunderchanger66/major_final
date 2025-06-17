#pragma once

#include <vector>
#include <utility> // for std::pair
#include <opencv2/opencv.hpp> 
#include <unordered_set>

//需要手动创建适合pair<int, int>的哈希函数，以便在unordered_set中使用
struct pair_hash 
{
    std::size_t operator()(const std::pair<int, int>& p) const 
    {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

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

    void getCoverage();//覆盖率
    void getRepeated();//重复率

private:
    returnpath returnPath;// 存储返回的路径和网格数据
    cv::Mat finalShow;// 最终显示的图像

    double emptyCount = 0; // 统计可通行的点数
    double coveredCount = 0; // 统计覆盖的点数
    double coverage = 0; // 覆盖率

    double repeatedCount = 0; // 统计重复的点数
    std::unordered_set<std::pair<int, int>, pair_hash> repeatedSet; // 用于存储重复的点
    double repeated = 0; // 重复率
};