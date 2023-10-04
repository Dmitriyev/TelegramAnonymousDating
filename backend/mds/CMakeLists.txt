cmake_minimum_required(VERSION 3.22.1)

project(mds)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

OPTION(AWS_SDK_PREFIX_PATH "Path where aws-sdk-cpp installed")

list(APPEND CMAKE_PREFIX_PATH ${AWS_SDK_PREFIX_PATH})
find_package(AWSSDK REQUIRED COMPONENTS s3 sts)

set(MDS_ROOT_DIR ${PROJECT_SOURCE_DIR}/..)
set(MDS_SOURCE_DIR ${MDS_ROOT_DIR}/mds)

add_subdirectory(${MDS_ROOT_DIR}/thirdparty/drogon drogon)
add_subdirectory(${MDS_ROOT_DIR}/lib/utils utils)

file(COPY_FILE ${MDS_SOURCE_DIR}/config/conf.json ${CMAKE_BINARY_DIR}/conf_template.json)

set(
    MDS_SOURCE_FILES
    ${MDS_SOURCE_DIR}/main.cpp
    ${MDS_SOURCE_DIR}/aws_adapter/adapter.cpp
    ${MDS_SOURCE_DIR}/config/config.cpp
    ${MDS_SOURCE_DIR}/handlers/handlers.cpp
)

add_executable(${PROJECT_NAME} ${MDS_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${MDS_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE ${AWSSDK_LINK_LIBRARIES} ${AWSSDK_PLATFORM_DEPS} drogon utils)