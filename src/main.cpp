#include <iostream>

#include <opencv2/opencv.hpp>
#include "imgprocess.hpp"
#include "pathplan.hpp"

int main(int, char**)
{
    //ImageProcessor imgProcessor;
    //imgProcessor.makeGrid();

    PathPlanner pathPlanner;

    std::vector<std::vector<int>> grid = pathPlanner.getGrid();

    cv::Mat visual(cv::Size(grid[0].size(), grid.size()), CV_8UC1);
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[i].size(); j++)
        {
            visual.at<uchar>(i, j) = (grid[i][j] == 0) ? 255 : 0; // 0 for passable, 255 for impassable
        }
    }
    cv::imshow("Grid Visual", visual);
    cv::waitKey(0);

    return 0;
    //std::cout << "Hello, from major_final!\n";
}
