#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

class ImageProcessor
{
public:
    ImageProcessor();
    ~ImageProcessor();

    void showRawMat();
    //void makeGrid();

    // 直接public
    std::vector<std::vector<int>> grid;// 网格数据，0表示可通行，1表示不可通行
    //std::vector<std::vector<int>> getGrid() const { return grid; }

    void showGrid();//转成可视化图像，必须要先调用

private:
    cv::Mat image;// 源图
    void makeGrid();
};