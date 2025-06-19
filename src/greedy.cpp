#include "greedy.hpp"
#include <iostream>

// std::vector<std::pair<int, int>> greedy::greedyPath()
// {
//     greddypath.clear();
//     int n = path.size();
//     if(n == 0) return greddypath;

//     int curr = 0;//當前點
//     for(int i = 0; i < n; i++)//遍歷每一個點
//     {
//         if(curr == 0)//第一個點直接插入
//             greddypath.emplace_back(path[0]);

//         // if(pathVisitd[i])//已訪問過直接跳過
//         //     continue;
//         pathVisitd[curr] = true;//當前點已訪問

//         int lengthmin = INT_MAX;
//         int length = lengthmin;
//         int indexmin = curr + 1;//默認下一個的點
//         for(int j = 0; j < n; j++)
//         {
//             if(!pathVisitd[j])
//             {
//                 length = findPath(dilategrid, path[curr], path[j]).size();
//                 if(length < lengthmin)
//                 {
//                     lengthmin = length;
//                     indexmin = j;
//                 }
//             }
//         }

//         greddypath.emplace_back(path[indexmin]);
//         curr = indexmin;
//     }
//     return greddypath;
// }

std::vector<std::pair<int, int>> greedy::greedyPath()
{
    pathVisitd.resize(path.size(), false);

    greedypath.clear();
    n = path.size();
    if(n == 0) return greedypath;

    pathVisitd.assign(n, false);
    int curr = 0;
    greedypath.emplace_back(path[curr]);
    pathVisitd[curr] = true;

    calculatedistance();//先算距離矩陣

    for(int step = 1; step < n; ++step)
    {
        int next = -1;
        int minLen = INT_MAX;
        for(int j = 0; j < n; ++j)
        {
            if(!pathVisitd[j])
            {
                int len = distanceMatrix[curr][j];
                if(len < minLen)
                {
                    minLen = len;
                    next = j;
                }
            }
        }
        if(next == -1) break; // 没有未访问点
        greedypath.emplace_back(path[next]);
        pathVisitd[next] = true;
        curr = next;
    }
    return greedypath;
}

void greedy::calculatedistance()
{
    n = path.size();
    distanceMatrix.resize(n, std::vector<int>(n, INT_MAX));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == j) continue;
            auto pathij = findPath(dilategrid, path[i], path[j]);
            std::cout << n << std::endl;
            if (!pathij.empty())
                distanceMatrix[i][j] = pathij.size();
        }
    }
}