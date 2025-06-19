#include "evaluator.hpp"
#include <opencv2/opencv.hpp>
#include <vector>
#include <utility>
#include <iostream>
#include <unordered_set>

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
    std::unordered_set<std::pair<int, int>, pair_hash> lastCarBody;
    for(const auto& p : returnPath.path)
    {
        int x = p.first;
        int y = p.second;
        std::unordered_set<std::pair<int, int>, pair_hash> thisCarBody;

        for(int dx = -3; dx <= 3; dx++)
        {
            for(int dy = -3; dy <= 3; dy++)
            {
                if(dx * dx + dy * dy > 9) continue;
                if(dx != 0 || dy != 0)
                {
                    int nx = x + dx, ny = y + dy;
                    if(nx < 0 || ny < 0 || nx >= visitedCar.size() || ny >= visitedCar[0].size())
                        continue;

                    visitedCar[nx][ny] = 1;
                    thisCarBody.insert({nx, ny});

                    // 只在不是上一次车身覆盖的点时才统计重复
                    if(repeatedSet.count({nx, ny}) && !lastCarBody.count({nx, ny}))
                    {
                        repeatedCount++;
                        finalShow.at<cv::Vec3b>(nx, ny) = cv::Vec3b(0, 255, 0);
                    }
                    else
                    {
                        finalShow.at<cv::Vec3b>(nx, ny) = cv::Vec3b(0, 0, 255);
                    }
                    repeatedSet.insert({nx, ny});
                }
            }
        }
        lastCarBody = std::move(thisCarBody);

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
}

void Evaluator::getCoverage()
{
    coverage = (coveredCount / emptyCount) * 100.0; // 计算覆盖率
    std::cout << "Empty Count: " << emptyCount << std::endl;
    std::cout << "Covered Count: " << coveredCount << std::endl;
    std::cout << "Coverage: " << coverage << "%" << std::endl;
}

void Evaluator::getRepeated()
{
    repeated = (repeatedCount / emptyCount) * 100.0; // 计算重复率
    std::cout << "Repeated Count: " << repeatedCount << std::endl;
    std::cout << "Repeated: " << repeated << "%" << std::endl;
}