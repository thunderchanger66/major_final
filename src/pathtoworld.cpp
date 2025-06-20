#include "pathtoworld.hpp"
#include <iostream>

void pathToWorld::pathtoworld()
{
    path.clear();
    for(int i = 0; i < road.size(); i++)
    {
        double wx = originX + resolution * road[i].first;
        double wy = originX + resolution * road[i].second;
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