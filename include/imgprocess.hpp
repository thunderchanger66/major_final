#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

class ImageProcessor
{
public:
    ImageProcessor(int dilateSize = 9); // 构造函数，默认膨胀大小为9*9
    ~ImageProcessor();

    void showRawMat();
    void makeGrid();
    void makeDilatedGrid();// 膨胀处理，生成膨胀后的网格数据

    // 直接public
    std::vector<std::vector<int>> grid;// 网格数据，0表示可通行，1表示不可通行
    std::vector<std::vector<int>> dilatedgrid;// 膨胀后的网格数据，0表示可通行，1表示不可通行
    //std::vector<std::vector<int>> getGrid() const { return grid; }

    void showGrid();//转成可视化图像，必须要先调用

    std::vector<std::vector<int>> region;//区域标记数据，0左1右，-1不可
    void gridRegion(const std::vector<std::vector<int>>& grid);

private:
    cv::Mat image;// 源图
    cv::Mat dilated;// 膨胀后的图，需对障碍物进行膨胀处理
};