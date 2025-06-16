#include <iostream>
#include <opencv2/opencv.hpp>
#include "imgprocess.hpp"
#include "pathplan.hpp"

int main(int, char**)
{
    //ImageProcessor imgProcessor;
    //imgProcessor.makeGrid();

    PathPlanner pathPlanner;
    pathPlanner.showGrid();

    pathPlanner.zigzagSweep();
    pathPlanner.showPath();

    cv::waitKey(0);
    return 0;
    //std::cout << "Hello, from major_final!\n";
}
