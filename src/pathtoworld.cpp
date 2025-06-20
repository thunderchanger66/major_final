#include "pathtoworld.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>

//坐標好像有點問題，調一下wx和wy的順序
void pathToWorld::pathtoworld()
{
    path.clear();
    for(int i = 0; i < road.size(); i++)
    {
        //這裏的wx和wy就要這樣，是反過來的
        double wy = originX + resolution * road[i].first;
        double wx = originX + resolution * road[i].second;
        path.emplace_back(wx, wy);
        //std::cout << "World: (" << wx << ", " << wy << ")" << std::endl;
    }
}

//简单等数量路径点离散
void pathToWorld::discretePath()
{
    discretepath.clear();
    int count = 0;
    for(int i = 0; i < path.size(); i++)
    {
        if(i % 5 == 0)
        {
            discretepath.emplace_back(path[i].first, path[i].second);
            std::cout << "World: (" << path[i].first << "," << path[i].second << ")" << std::endl;
            count++;
        }
    }
    std::cout << "Count: " << count << std::endl;
}

//節省點數的根據曲率特徵保留點
void pathToWorld::curvedisPath()
{
    discretepath.clear();
    int count = 0;

    // 匿名函数，获得夹角
    auto calAngle = [](std::pair<double, double> a, std::pair<double, double> b, std::pair<double, double> c)
    {
        std::pair<double, double> u(b.first - a.first, b.second - a.second);
        std::pair<double, double> v(c.first - b.first, c.second - b.second);
        double dot = u.first * v.first + u.second * v.second;
        double cross = u.first * v.second - u.second * v.first;
        double angle = std::atan2(std::abs(cross), dot); // 返回0~π范围的角度
        return angle;
    };

    discretepath.emplace_back(path[0]);//直接加入第一個點
    count++;
    for(int i = 1; i < path.size() - 1; i++)//從第二個點到倒數第二個點
    {
        double angle = calAngle(path[i - 1], path[i], path[i + 1]);
        if(angle < CV_PI * 0.1)//接近直綫的路徑點會直接跳過
            continue;
        else
        {
            discretepath.emplace_back(path[i]);
            std::cout << "World: (" << path[i].first << "," << path[i].second << ")" << std::endl;
            count++;
        }
    }
    if(path.size() > 1) 
    {
        discretepath.emplace_back(path.back());
        count++;
    }
    std::cout << "Count: " << count << std::endl;

    //嘗試顯示離散后的路徑
    cv::namedWindow("Discrete Path", cv::WINDOW_NORMAL);
    cv::Mat img = cv::Mat::zeros(cv::Size(1600, 700), CV_8UC3);//改了上面path的wx和wy后，這裏也要同步修改
    for(const auto& p : discretepath)
        cv::circle(img, cv::Point(p.first * 100, p.second * 100), 3, cv::Scalar(0, 0, 255), -1);

    for(int i = 1; i < discretepath.size(); i++) 
    {
        cv::line(img, cv::Point(discretepath[i - 1].first * 100, discretepath[i - 1].second * 100),
            cv::Point(discretepath[i].first * 100, discretepath[i].second * 100),
            cv::Scalar(0, 255, 0), 2);
        cv::imshow("Discrete Path", img);
        cv::waitKey(100);
    }

}