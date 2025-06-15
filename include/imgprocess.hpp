#pragma once

#include <opencv2/opencv.hpp>

class ImageProcessor
{
public:
    ImageProcessor();
    ~ImageProcessor();

    void showRawMat();

private:
    cv::Mat image;// 源图
};