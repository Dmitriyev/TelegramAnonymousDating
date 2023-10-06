cmake_minimum_required(VERSION 3.22.1)

project(server_config)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SERVER_ROOT_DIR ${PROJECT_SOURCE_DIR}/..)

add_subdirectory(${SERVER_ROOT_DIR}/utils utils)

set(
    SERVER_CONFIG_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/config.cpp
)

add_library(${PROJECT_NAME} ${SERVER_CONFIG_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC utils jsoncpp)

