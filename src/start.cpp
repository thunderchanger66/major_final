#include "start.hpp"
#include "pathplan.hpp"
#include "astar.hpp"
#include <vector>
#include <utility>
#include "evaluator.hpp"

returnpath returnPath()
{
    PathPlanner pathPlanner;// 创建路径规划器对象
    pathPlanner.showGrid();// 显示网格地图
    //pathPlanner.zigzagSweep();//之字形规划原始断续路径
    //现在采用先大概分区的方法，暂时分了两个，左0右1
    for(int i = 0; i < 2; i++)//先左后右
        pathPlanner.zigzagSweepRegion(i);//对每个区域进行之字形规划

    std::vector<std::pair<int, int>> zigzagPath = pathPlanner.getPath();// 获取之字形路径

    // 进行A*路径规划
    Astar astar;// 创建A*路径规划对象
    std::vector<std::pair<int, int>> fullPath;// 存储完整路径
    for(int i = 0; i < zigzagPath.size(); i++)
    {
        if(i == 0)
        {
            fullPath.push_back(zigzagPath[i]);// 第一个点直接加入
            continue;
        }
        // 对于后续点，使用A*算法连接前后点
        std::vector<std::pair<int, int>> subPath = astar.findPath(pathPlanner.dilatedgrid, zigzagPath[i - 1], zigzagPath[i]);
        if(!subPath.empty())
        {
            //如果找到路径，将其加入完整路径中
            fullPath.insert(fullPath.end(), subPath.begin() + 1, subPath.end()); // 避免重复添加起点
        }
    }

    pathPlanner.showRawPath();//原始路径
    astar.showAStarPath(fullPath, pathPlanner.grid);// 显示A*规划后的路径

    cv::waitKey(0);

    return {fullPath, pathPlanner.grid}; // 返回完整路径和网格数据
}

void start()
{
    returnpath returnedPath = returnPath();//获得路径及原始栅格地图
    Evaluator evaluator(returnedPath); // 创建评估器对象
    evaluator.beTheCar(); // 执行评估

    evaluator.getCoverage(); // 获取覆盖率
    evaluator.getRepeated(); // 获取重复率
    cv::waitKey(0); // 等待按键
}