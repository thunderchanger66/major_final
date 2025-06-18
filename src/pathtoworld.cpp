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