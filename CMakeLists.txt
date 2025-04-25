cmake_minimum_required(VERSION 3.10)

# 设置项目名称和语言
project(string_validator VERSION 1.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件
add_executable(string_validator src/daduanmian.cpp)

# 安装目标
install(TARGETS string_validator DESTINATION bin) 