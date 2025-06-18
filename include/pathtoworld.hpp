#pragma once

#include <vector>
#include <utility>

class pathToWorld
{
private:
    //地图原点位置
    const double originX = -0.37;
    const double originY = -0.501;
    const double resolution = 0.05;//一个像素在世界坐标系中是0.05m

    std::vector<std::pair<int, int>> road;//传进来的原始路径
    std::vector<std::pair<int, int>> path;//换算到世界坐标系的路径
public:
    pathToWorld(const std::vector<std::pair<int, int>>& road) : road(road) {}

    void pathtoworld();

    std::vector<std::pair<int, int>> discretepath;
    void discretePath();
};