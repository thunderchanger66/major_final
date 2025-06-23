#pragma once

#include <vector>
#include <utility>
#include <fstream>

class pathToWorld
{
private:
    //地图原点位置
    const double originX = -0.37 - 0.38;
    const double originY = -0.501 - 0.43;
    const double resolution = 0.05;//一个像素在世界坐标系中是0.05m

    std::vector<std::pair<int, int>> road;//传进来的原始路径
    std::vector<std::pair<double, double>> path;//换算到世界坐标系的路径

    std::ofstream fout;
public:
    pathToWorld(const std::vector<std::pair<int, int>>& road, const std::string& filename) : road(road), fout(filename) {}
    ~pathToWorld() { fout.close(); }

    void pathtoworld();

    std::vector<std::pair<double, double>> discretepath;
    void discretePath();
    
    //嘗試根據曲率來判定點
    void curvedisPath();

    //输出到CSV文件
    void outToCSV();
};