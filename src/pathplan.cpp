#include "pathplan.hpp"

PathPlanner::PathPlanner() : ImageProcessor(9), rows(grid.size()), cols(grid[0].size())
{
    makeGrid();//必须先拿到栅格地图
    makeDilatedGrid();//生成膨胀后的栅格地图，现在路径规划正式改用膨胀后的栅格地图
    visited.resize(dilatedgrid.size(), std::vector<bool>(dilatedgrid[0].size(), false));
}

void PathPlanner::zigzagSweep()
{
    for(int i = 0; i < rows; i+=9)//这里i跳的行数和小车的大小有关
    {
        //偶数行从左往右，否则从右往左
        if(i % 2 == 0)//这里的j++和j--为了消去一些点
        {
            for(int j = 0; j < cols; j+=5)
            {
                if(dilatedgrid[i][j] == 0 && !visited[i][j])
                {
                    visited[i][j] = true;//已经访问
                    path.emplace_back(i, j); //添加到路径中
                }
                // if(grid[i][j] == 0)//不需要已经访问了，在A*中会处理
                // {
                //     path.emplace_back(i, j); //添加到路径中
                // }
            }
        }
        else
        {
            for(int j = cols - 1; j >= 0; j-=5)
            {
                if(dilatedgrid[i][j] == 0 && !visited[i][j])
                {
                    visited[i][j] = true;//已经访问
                    path.emplace_back(i, j); //添加到路径中
                }
            }
        }
    }
}

void PathPlanner::showRawPath()
{
    cv::Mat visual(cv::Size(cols, rows), CV_8UC3, cv::Scalar(255, 255, 255));//白色背景
    cv::namedWindow("RawPath Visual", cv::WINDOW_NORMAL);
    
    //画原始地图的栅格图
    for(int i = 0; i < grid.size(); i++)//这里要采用三通道彩色图的画法
    {
        for(int j = 0; j < grid[i].size(); j++)
        {
            if(grid[i][j] == 0)
                visual.at<cv::Vec3b>(i, j) = cv::Vec3b(255, 255, 255); // 可通行为白色
            else
                visual.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);       // 障碍为黑色
        }
    }

    for(const auto& p : path)
    {
        int x = p.first;
        int y = p.second;
        visual.at<cv::Vec3b>(x, y) = cv::Vec3b(0, 0, 255); // 红色表示路径点
        cv::imshow("RawPath Visual", visual);
        //cv::waitKey(1);
    }
    //cv::imshow("Path Visual", visual);
}

