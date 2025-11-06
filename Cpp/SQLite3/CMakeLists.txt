cmake_minimum_required(VERSION 3.14)
project(sql_crud_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SQLite3 REQUIRED)

add_executable(sql_crud_example main.cpp)
target_link_libraries(sql_crud_example SQLite::SQLite3)
