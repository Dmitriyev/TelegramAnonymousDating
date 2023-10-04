cmake_minimum_required(VERSION 3.22.1)

project(utils)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(UTILS_ROOT_DIR ${PROJECT_SOURCE_DIR}/..)

set(
    UTILS_SOURCES
    json_utils.cpp
)

add_library(${PROJECT_NAME} ${UTILS_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${UTILS_ROOT_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC jsoncpp)

