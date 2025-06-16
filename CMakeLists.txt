cmake_minimum_required(VERSION 3.10.0)
project(major_final VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

set(OpenCV_DIR
    "D:\\opencccc\\vscv\\install\\x64\\mingw\\lib"
)
find_package(OpenCV REQUIRED)

add_executable(major_final 
    src/main.cpp
    src/imgprocess.cpp
    src/pathplan.cpp
    src/astar.cpp
    src/start.cpp
)

target_include_directories(major_final 
    PRIVATE 
        ${OpenCV_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(major_final PRIVATE ${OpenCV_LIBS})
