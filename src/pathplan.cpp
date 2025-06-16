#include "pathplan.hpp"

PathPlanner::PathPlanner() : ImageProcessor(), rows(grid.size()), cols(grid[0].size())
{
    makeGrid();//必须先拿到栅格地图
    visited.resize(grid.size(), std::vector<bool>(grid[0].size(), false));
}

void PathPlanner::zigzagSweep()
{
    for(int i = 0; i < rows; i++)
    {
        //偶数行从左往右，否则从右往左
        if(i % 2 == 0)
        {
            for(int j = 0; j < cols; j++)
            {
                if(grid[i][j] == 0 && !visited[i][j])
                {
                    visited[i][j] = true;//已经访问
                    path.emplace_back(i, j); //添加到路径中
                }
            }
        }
        else
        {
            for(int j = cols - 1; j >= 0; j--)
            {
                if(grid[i][j] == 0 && !visited[i][j])
                {
                    visited[i][j] = true;//已经访问
                    path.emplace_back(i, j); //添加到路径中
                }
            }
        }
    }
}

void PathPlanner::showPath()
{
    cv::Mat visual(cv::Size(cols, rows), CV_8UC3, cv::Scalar(255, 255, 255));//白色背景
    cv::namedWindow("Path Visual", cv::WINDOW_NORMAL);
    for(const auto& p : path)
    {
        int x = p.first;
        int y = p.second;
        visual.at<cv::Vec3b>(x, y) = cv::Vec3b(0, 0, 255); // 红色表示路径点
        cv::imshow("Path Visual", visual);
        cv::waitKey(1);
    }
    //cv::imshow("Path Visual", visual);
}