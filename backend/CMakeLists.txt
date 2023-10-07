cmake_minimum_required(VERSION 3.22.1)

project(server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/thirdparty/drogon)

set(SERVER_SOURCE_DIR ${PROJECT_SOURCE_DIR}/server)
set(HANDLERS_SOURCE_DIR ${SERVER_SOURCE_DIR}/handlers)

set(HANDLERS_SOURCES 
	${HANDLERS_SOURCE_DIR}/account.cpp
	${HANDLERS_SOURCE_DIR}/search.cpp
)

file(COPY_FILE ${SERVER_SOURCE_DIR}/config/conf.json ${CMAKE_BINARY_DIR}/conf_template.json)

set(
    SERVER_SOURCE_FILES
    ${SERVER_SOURCE_DIR}/main.cpp
    ${SERVER_SOURCE_DIR}/config/config.cpp
    ${SERVER_SOURCE_DIR}/db_adapter/adapter.cpp
    ${SERVER_SOURCE_DIR}/db_adapter/redis.cpp
    ${SERVER_SOURCE_DIR}/utils/json_utils.cpp
    ${SERVER_SOURCE_DIR}/common/common_structures.cpp 
    ${HANDLERS_SOURCES}
)

add_executable(${PROJECT_NAME} ${SERVER_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${SERVER_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE drogon pqxx)

