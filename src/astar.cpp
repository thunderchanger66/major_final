#include "astar.hpp"
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <opencv2/opencv.hpp>

std::vector<std::pair<int, int>> Astar::findPath(const std::vector<std::vector<int>>& grid, std::pair<int, int> start, std::pair<int, int> goal)
{
    int rows = grid.size();
    int cols = grid[0].size();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false)); // 已经访问
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> open; // 优先队列

    Node* startNode = new Node{start.first, start.second, 0, heuristic(start, goal), nullptr};// 创建起点节点
    open.push(startNode);

    while(!open.empty())
    {
        Node* current = open.top();// 获取当前节点
        open.pop();// 弹出当前节点
        int x = current->x, y = current->y;
        if(visited[x][y]) continue; // 如果已经访问过，跳过
        visited[x][y] = true;// 已经访问

        if(x == goal.first && y == goal.second) //如果到达目标节点
        {
            std::vector<std::pair<int, int>> path;
            while(current)//回溯路径
            {
                path.emplace_back(current->x, current->y);
                current = current->parent;//回溯到父节点
            }
            std::reverse(path.begin(), path.end());//反转路径
            return path;
        }

        // 遍历四个方向
        for(int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];//新的x坐标
            int ny = y + dy[i];//新的y坐标
            if(inbounds(nx, ny, rows, cols) && !grid[nx][ny] && !visited[nx][ny])//如果在边界内并且没有访问过且可通行
            {
                Node* neighbor = new Node{nx, ny, current->g + 1, heuristic({nx, ny}, goal), current};//创建邻居节点
                open.push(neighbor);//加入优先队列
            }
        }
    }

    return {};// 如果没有路径，返回空
}

void Astar::showAStarPath(const std::vector<std::pair<int, int>>& path, const std::vector<std::vector<int>>& grid)
{
    cv::Mat visual(cv::Size(grid[0].size(), grid.size()), CV_8UC3, cv::Scalar(255, 255, 255));//白色背景
    cv::namedWindow("FinalPath Visual", cv::WINDOW_NORMAL);
    
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
        cv::imshow("FinalPath Visual", visual);
        //cv::waitKey(1);
    }
}