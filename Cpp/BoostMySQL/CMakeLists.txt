cmake_minimum_required(VERSION 3.21)
project(BoostMySQLDemo CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS NO)

find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(mysql_demo main.cpp)

target_link_libraries(mysql_demo
    PRIVATE
        boost::boost
        OpenSSL::SSL
)
