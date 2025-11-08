cmake_minimum_required(VERSION 3.28)
project(mysql_concpp_example LANGUAGES CXX)

find_package(mysql-concpp REQUIRED)
find_package(OpenSSL REQUIRED)

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
        mysql::concpp
        OpenSSL::SSL
        OpenSSL::Crypto
)
