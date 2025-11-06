# C++ MariaDB SOCI Demo

This project demonstrates connecting to MariaDB from C++ using SOCI, building with CMake and Conan, and running MariaDB with Docker Compose.

## Prerequisites

- Docker & Docker Compose
- Conan
- CMake
- g++ (or similar)

## Running MariaDB

MariaDB should run on `localhost:3306` with:
- Database: `test_db`
- User: `test_user`
- Password: `test_pass`

## Installing dependencies

Using `build` folder

## Debug build
```sh
conan install .. --build=missing -pr:b=default -s build_type=Debug
cmake .. --preset conan-debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cd Debug
make
```
* Use `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON` to export list of compile commands
* For cmake<3.23 :
```sh
cd Debug
cmake ../.. -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
```

## Release build
```sh
conan install .. --build=missing -pr:b=default -s build_type=Release
cmake .. --preset conan-release
cd Release
make
```

## Building

```sh
cmake .
cmake --build .
```

## Running

```sh
./cpp_mariadb_soci_demo
```

