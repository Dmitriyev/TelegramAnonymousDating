cmake_minimum_required(VERSION 3.22.1)

project(auth_lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SERVER_ROOT_DIR ${PROJECT_SOURCE_DIR}/..)

if (NOT TARGET utils)
    add_subdirectory(${SERVER_ROOT_DIR}/utils utils)
endif()

set(
    AUTH_LIB_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/auth.cpp
)

add_library(${PROJECT_NAME} ${AUTH_LIB_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC utils jsoncpp drogon crypto)

