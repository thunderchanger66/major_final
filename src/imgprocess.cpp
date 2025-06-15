#include <imgprocess.hpp>

ImageProcessor::ImageProcessor()
{
    cv::Mat image = cv::imread("E:\\STUDY\\Junior.down\\major_final\\map\\carto_map.pgm", cv::IMREAD_UNCHANGED);
    if(image.empty())
    {
        std::cerr << "Error: Could not open or find the image!\n";
    }
    else
    {
        cv::imshow("Raw Image", image);
        cv::waitKey(0);
    }
}

ImageProcessor::~ImageProcessor()
{
    cv::destroyAllWindows();
}