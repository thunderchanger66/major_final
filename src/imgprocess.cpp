#include <imgprocess.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

ImageProcessor::ImageProcessor(int dilateSize)
{
    //cv::Mat image = cv::imread("E:\\STUDY\\Junior.down\\major_final\\map\\carto_map.pgm", cv::IMREAD_UNCHANGED);
    image = cv::imread("E:\\STUDY\\Junior.down\\major_final\\map\\map2.png", cv::IMREAD_GRAYSCALE);
    if(image.empty())
    {
        std::cerr << "Error: Could not open or find the image!\n";
    }
    else
    {
        cv::namedWindow("Raw Image", cv::WINDOW_NORMAL);
        cv::imshow("Raw Image", image);
        //cv::waitKey(0);
    }

    // Initialize grid with zeros
    grid.resize(image.rows, std::vector<int>(image.cols, 0));
    //makeGrid();//必须先拿到栅格地图

    cv::Mat binary;
    cv::threshold(image, binary, 230, 255, cv::THRESH_BINARY_INV); // 将图像二值化

    //直接膨胀
    //dilated = image.clone();
    //cv::Mat obstacleMask = (image == 0);// 障碍物的掩码
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(dilateSize, dilateSize));
    cv::dilate(binary, dilated, kernel);

    dilatedgrid.resize(dilated.rows, std::vector<int>(dilated.cols, 0));// 膨胀后的网格数据

    cv::namedWindow("Dilated Image", cv::WINDOW_NORMAL);
    cv::imshow("Dilated Image", dilated);
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
            //std::cout << (int)image.at<uchar>(i, j) << " ";
            if((int)image.at<uchar>(i, j) == 255)
                std::cout << " ";
            else if((int)image.at<uchar>(i, j) == 0)
                std::cout << "*";
            else
                std::cout << "?";
        }
        std::cout << std::endl;
    }
}

void ImageProcessor::makeGrid()
{
    for(int i = 0; i < image.rows; i++)
        for(int j = 0; j < image.cols; j++)
        {
            if((int)image.at<uchar>(i, j) == 255)
                grid[i][j] = 0;//可通行
            else
                grid[i][j] = 1;//不可通行         
        }
}

void ImageProcessor::makeDilatedGrid()
{
    for(int i = 0; i < dilated.rows; i++)
        for(int j = 0; j < dilated.cols; j++)
        {
            if((int)dilated.at<uchar>(i, j) == 0)//这里0表示可通行区域
                dilatedgrid[i][j] = 0;//可通行
            else
                dilatedgrid[i][j] = 1;//不可通行         
        }
}

void ImageProcessor::showGrid()
{
    cv::Mat visual(cv::Size(grid[0].size(), grid.size()), CV_8UC1);
    cv::namedWindow("Grid Visual", cv::WINDOW_NORMAL);
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[i].size(); j++)
        {
            visual.at<uchar>(i, j) = (grid[i][j] == 0) ? 255 : 0; // 0 for passable, 255 for impassable
        }
    }
    cv::imshow("Grid Visual", visual);
    //cv::waitKey(0);
}