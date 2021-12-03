# CMakeList.txt: ZCScripter 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 将源代码添加到此项目的可执行文件。
add_executable (ZCScripter "Core/Script_System.cpp""Core/Script_Read.cpp" "Core/Script.h" "Core/Script_Analyze.cpp" "ZCScripter.cpp" "Converter/Converter.h" "Converter/String_To_WString.cpp" "Converter/UCS-2_TO_UTF-8.cpp")

# TODO: 如有需要，请添加测试并安装目标。
