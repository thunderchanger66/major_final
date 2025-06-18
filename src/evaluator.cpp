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
    for(const auto& p : returnPath.path)//半径应该要有3个像素，即15cm左右
    {
        int x = p.first;
        int y = p.second;

        for(int dx = -3; dx <= 3; dx++)
        {
            for(int dy = -3; dy <= 3; dy++)
            {
                if(dx * dx + dy * dy > 9) continue; // 跳过不在半径内的点，使其看起来更像一个圆形，注释掉则为方形
                if(dx != 0 || dy != 0)
                {
                    visitedCar[x + dx][y + dy] = 1; // 标记为已访问

                    //插入到hash表，进行重复点的计数
                    auto [it, inserted] = repeatedSet.insert({x + dx, y + dy});
                    if(!inserted)
                        {
                            repeatedCount++; // 如果插入失败，说明是重复点
                            finalShow.at<cv::Vec3b>(x + dx, y + dy) = cv::Vec3b(0, 255, 0); // 红色表示路径点
                            continue;
                        }

                    finalShow.at<cv::Vec3b>(x + dx, y + dy) = cv::Vec3b(0, 0, 255); // 红色表示路径点
                }
            }
        }

        //小车移动会重复计算上一个时刻与这一个时刻重复的点，也就是每次经过原始路径点一个像素的距离，这是不必要的，需要减去
        //计算出单个车占像素29个，减去每次移动的7个像素
        repeatedCount -= (29 - 7);
        //方形小车测试
        //repeatedCount -= (49 - 7); // 方形小车占49个像素，减去每次移动的7个像素

        cv::imshow("FinalShow", finalShow);
        //cv::waitKey(1);//决定是否用这里仿真来显示 
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