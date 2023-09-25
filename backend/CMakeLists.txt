cmake_minimum_required(VERSION 3.22.1)

project(server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DROGON_DIRECTORY ${PROJECT_SOURCE_DIR}/thirdparty/drogon)
add_subdirectory(${DROGON_DIRECTORY})

set(HANDLERS_SOURCES 
	server/handlers/register.cpp
)

add_executable(${PROJECT_NAME} server/main.cpp ${HANDLERS_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE drogon)

