cmake_minimum_required(VERSION 3.22.1)

project(mds)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

OPTION(AWS_SDK_PREFIX_PATH "Path where aws-sdk-cpp installed")

list(APPEND CMAKE_PREFIX_PATH ${AWS_SDK_PREFIX_PATH})
find_package(AWSSDK REQUIRED COMPONENTS s3 sts)

set(MDS_ROOT_DIR ${PROJECT_SOURCE_DIR}/..)

add_subdirectory(${MDS_ROOT_DIR}/thirdparty/drogon drogon)
add_subdirectory(${MDS_ROOT_DIR}/lib/server_config server_config)
add_subdirectory(${MDS_ROOT_DIR}/lib/auth_lib auth_lib)
if (NOT TARGET utils)
    add_subdirectory(${MDS_ROOT_DIR}/lib/utils utils)
endif()

file(COPY_FILE ${PROJECT_SOURCE_DIR}/config/conf.json ${CMAKE_BINARY_DIR}/conf_template.json)

set(
    MDS_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/aws_adapter/adapter.cpp
    ${PROJECT_SOURCE_DIR}/config/config.cpp
    ${PROJECT_SOURCE_DIR}/handlers/handlers.cpp
)

add_executable(${PROJECT_NAME} ${MDS_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE ${AWSSDK_LINK_LIBRARIES} ${AWSSDK_PLATFORM_DEPS} drogon utils server_config auth_lib)
