# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_SYSTEM_NAME Windows)
#SET(CMAKE_CXX_FLAGS_DEBUG "-g2 -m64 -std=c++17 -Wall -static-libgcc -static-libstdc++ -fexec-charset=GBK")


project ("ZCScripter")

# 包含子项目。
add_subdirectory ("ZCScripter")
