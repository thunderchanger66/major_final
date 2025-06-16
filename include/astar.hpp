#pragma once

#include <utility>
#include <vector>
#include <cmath>

struct Node
{
    int x, y; // 节点坐标
    int g, h; // g为起点到当前节点的代价，h为当前节点到终点的估计代价
    Node* parent; // 父节点指针
    int f() const { return g + h;} // f值为g值和h值之和
};

struct CompareNode
{
    bool operator()(const Node* a, const Node* b) const
    {
        return a->f() > b->f(); // 小顶堆，f值小的优先
    }
};

class Astar
{
private:
    int heuristic(std::pair<int, int> a, std::pair<int, int> b) const
    {
        return std::abs(a.first - b.first) + std::abs(a.second - b.second); // 曼哈顿距离
    }

    bool inbounds(int x, int y, int rows, int cols) const
    {
        return (x >= 0 && x < rows && y >= 0 && y < cols);
    }

    const int dx[4] = {-1, 1, 0, 0}; // 上下左右移动的x偏移
    const int dy[4] = {0, 0, -1, 1}; // 上下左右移动的y偏移

public:
    //A*路径规划实现
    std::vector<std::pair<int, int>> findPath(const std::vector<std::vector<int>>& grid, std::pair<int, int> start, std::pair<int, int> goal);

    //显示A*规划后的路径
    void showAStarPath(const std::vector<std::pair<int, int>>& path, const std::vector<std::vector<int>>& grid);
};