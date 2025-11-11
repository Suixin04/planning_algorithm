# 1. CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 2. 项目名称
project(PathPlannerViz)

# 3. 设置 C++ 标准 (推荐 C++17, 与 ROS 2 保持一致)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 4. 寻找 OpenCV 库 
#    这是最关键的一步。它会查找你系统上安装的 OpenCV。
#    'REQUIRED' 表示如果找不到，CMake 将会报错。
find_package(OpenCV REQUIRED)

# (可选) 包含头文件目录 (新版 CMake 不一定需要，但写上更保险)
include_directories(${OpenCV_INCLUDE_DIRS})

# 5. 定义我们的可执行文件
#    它会由 src/main.cpp 和 src/GridMap.cpp 编译而来
add_executable(planner_viz
    src/main.cpp
    src/GridMap.cpp
    src/BFSPlanner.cpp
    src/DFSPlanner.cpp
    src/DijkstraPlanner.cpp
    src/AstarPlanner.cpp
)

# 6. 将我们的程序与 OpenCV 库链接起来
#    这是告诉编译器：“在最后生成 planner_viz 时，
#    把 OpenCV 的功能(如 cv::imshow)也编译进去。”
target_link_libraries(planner_viz ${OpenCV_LIBRARIES})