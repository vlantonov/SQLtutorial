cmake_minimum_required(VERSION 3.21)
project(mariadb_crud_example LANGUAGES CXX)

find_package(mariadb-connector-c REQUIRED)

add_executable(
    ${PROJECT_NAME} 
        main.cpp
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE 
        mariadb-connector-c::mariadb-connector-c
)