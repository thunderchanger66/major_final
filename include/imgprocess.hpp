#pragma once

#include <opencv2/opencv.hpp>

class ImageProcessor
{
public:
    ImageProcessor();
    ~ImageProcessor();

private:
    cv::Mat image;// 源图
};