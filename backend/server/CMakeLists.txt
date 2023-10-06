cmake_minimum_required(VERSION 3.22.1)

project(server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SERVER_ROOT_DIR ${PROJECT_SOURCE_DIR}/..)

add_subdirectory(${SERVER_ROOT_DIR}/thirdparty/drogon drogon)
add_subdirectory(${SERVER_ROOT_DIR}/lib/server_config server_config)
# add_subdirectory(${SERVER_ROOT_DIR}/lib/utils utils)

set(HANDLERS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/handlers)

set(HANDLERS_SOURCES 
	${HANDLERS_SOURCE_DIR}/account.cpp
)

file(COPY_FILE ${PROJECT_SOURCE_DIR}/config/conf.json ${CMAKE_BINARY_DIR}/conf_template.json)

set(
    SERVER_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/config/config.cpp
    ${PROJECT_SOURCE_DIR}/db_adapter/adapter.cpp
    ${PROJECT_SOURCE_DIR}/common/common_structures.cpp 
    ${HANDLERS_SOURCES}
)

add_executable(${PROJECT_NAME} ${SERVER_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE drogon pqxx utils server_config)

