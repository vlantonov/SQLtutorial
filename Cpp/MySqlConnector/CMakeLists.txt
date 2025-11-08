cmake_minimum_required(VERSION 3.28)
project(mysql_concpp_example LANGUAGES CXX)

# sudo apt-get install libmysqlcppconn-dev

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
        mysqlcppconn
        # mysqlcppconn-static
)
