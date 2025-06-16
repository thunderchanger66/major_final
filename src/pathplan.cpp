#include "pathplan.hpp"

PathPlanner::PathPlanner() : ImageProcessor() 
{
    makeGrid();
    visited.resize(getGrid().size(), std::vector<bool>(getGrid()[0].size(), false));
}

void PathPlanner::zigzagSweep()
{
    
}