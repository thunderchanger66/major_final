#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

class ImageProcessor
{
public:
    ImageProcessor();
    ~ImageProcessor();

    void showRawMat();
    void makeGrid();

    std::vector<std::vector<int>> getGrid() const { return grid; }

private:
    cv::Mat image;// 源图
    std::vector<std::vector<int>> grid;// 网格数据，0表示可通行，1表示不可通行

};