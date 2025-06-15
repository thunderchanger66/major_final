#include <imgprocess.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

ImageProcessor::ImageProcessor()
{
    //cv::Mat image = cv::imread("E:\\STUDY\\Junior.down\\major_final\\map\\carto_map.pgm", cv::IMREAD_UNCHANGED);
    cv::Mat image = cv::imread("E:\\STUDY\\Junior.down\\major_final\\map\\map2.png", cv::IMREAD_GRAYSCALE);
    if(image.empty())
    {
        std::cerr << "Error: Could not open or find the image!\n";
    }
    else
    {
        cv::namedWindow("Raw Image", cv::WINDOW_NORMAL);
        cv::imshow("Raw Image", image);
        cv::waitKey(0);
    }
}

ImageProcessor::~ImageProcessor()
{
    cv::destroyAllWindows();
}

void ImageProcessor::showRawMat()
{
    for(int i = 0; i < image.rows; i++)
    {
        for(int j = 0; j < image.cols; j++)
        {
            std::cout << (int)image.at<uchar>(i, j) << " ";
        }
        std::cout << std::endl;
    }
}