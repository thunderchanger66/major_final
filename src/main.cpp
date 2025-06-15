#include <iostream>

#include <opencv2/opencv.hpp>

int main(int, char**)
{
    cv::Mat image = cv::imread("E:\\STUDY\\Junior.down\\major_final\\map\\carto_map.pgm", cv::IMREAD_UNCHANGED);
    if(image.empty())
    {
        std::cerr << "Error: Could not open or find the image!\n";
        return -1;
    }
    cv::imshow("Display Image", image);
    cv::waitKey(0);

    std::cout << "Hello, from major_final!\n";
}
