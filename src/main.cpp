#include <iostream>

#include <opencv2/opencv.hpp>
#include <imgprocess.hpp>

int main(int, char**)
{
    ImageProcessor imgProcessor;
    imgProcessor.makeGrid();

    std::vector<std::vector<int>> grid = imgProcessor.getGrid();
    for(auto& row : grid)
    {
        for(auto& cell : row)
        {
            if(cell == 0)
                std::cout << " ";
            else
                std::cout << "*";
        }
        std::cout << std::endl;
    }

    return 0;
    //std::cout << "Hello, from major_final!\n";
}
