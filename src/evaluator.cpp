#include "evaluator.hpp"
#include <opencv2/opencv.hpp>
#include <vector>
#include <utility>
#include <iostream>

void Evaluator::beTheCar()
{
    cv::namedWindow("FinalShow", cv::WINDOW_NORMAL);
    //画原始地图的栅格图
    for(int i = 0; i < returnPath.grid.size(); i++)//这里要采用三通道彩色图的画法
    {
        for(int j = 0; j < returnPath.grid[i].size(); j++)
        {
            if(returnPath.grid[i][j] == 0)
            {
                visitedCar[i][j] = 0; // 可通行区域标记为0
                emptyCount++; // 统计可通行的点数
                finalShow.at<cv::Vec3b>(i, j) = cv::Vec3b(255, 255, 255); // 可通行为白色
            }
            else
            {
                visitedCar[i][j] = -1; // 障碍区域标记为-1
                finalShow.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);       // 障碍为黑色
            }
        }
    }
    //画路径
    for(const auto& p : returnPath.path)//半径应该要有3个像素，即15cm左右
    {
        int x = p.first;
        int y = p.second;

        for(int dx = -3; dx <= 3; dx++)
        {
            for(int dy = -3; dy <= 3; dy++)
            {
                if(dx * dx + dy * dy > 9) continue; // 跳过不在半径内的点
                if(dx != 0 || dy != 0)
                {
                    visitedCar[x + dx][y + dy] = 1; // 标记为已访问
                    finalShow.at<cv::Vec3b>(x + dx, y + dy) = cv::Vec3b(0, 0, 255); // 红色表示路径点
                }
            }
        }

        cv::imshow("FinalShow", finalShow);
        cv::waitKey(1);
    }
    //统计覆盖的点数，用visitedCar数组
    for(int i = 0; i < visitedCar.size(); i++)
    {
        for(int j = 0; j < visitedCar[i].size(); j++)
        {
            if(visitedCar[i][j] == 1)
                coveredCount++; // 统计覆盖的点数
        }
    }
    //for testing
    std::cout << "Empty Count: " << emptyCount << std::endl;
    std::cout << "Covered Count: " << coveredCount << std::endl;
}