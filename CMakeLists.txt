cmake_minimum_required(VERSION 3.10)
project(RayTracing VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 创建可执行文件
add_executable(render "render.cpp")
