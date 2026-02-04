# 最低CMake版本要求（适配ESP-IDF v5.x）
cmake_minimum_required(VERSION 3.16)

# 项目名（自定义，比如esp32s3-mini-test）
set(PROJECT_NAME esp32s3-mini-test)

# 引入ESP-IDF的核心构建脚本（ESP-IDF自动识别，无需改路径）
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# 构建项目
project(${PROJECT_NAME})