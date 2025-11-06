# C++ SQL CRUD Example Project

This project demonstrates how to perform SQL operations (Create, Read, Update, Delete) using C++, CMake, and Conan for dependency management. The project uses the [SQLite3](https://www.sqlite.org/index.html) database for simplicity.

## Prerequisites

- [Conan](https://conan.io/) (package manager for C++)
- [CMake](https://cmake.org/) (version 3.14+)
- A C++ compiler (e.g., g++, clang++)

## Setup Instructions

Using `build` folder

### Debug build
```
conan install .. --build=missing -pr:b=default -s build_type=Debug
cmake .. --preset conan-debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cd Debug
make
```
* Use `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON` to export list of compile commands
* For cmake<3.23 :
```
cd Debug
cmake ../.. -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
```

### Release build
```
conan install .. --build=missing -pr:b=default -s build_type=Release
cmake .. --preset conan-release
cd Release
make
```

### Run the executable:

   ```sh
   ./build/Debug/sql_crud_example
   ```

   ```sh
   ./build/Release/sql_crud_example
   ```

## What it does

- Creates a table
- Inserts a record
- Reads/prints records
- Updates a record
- Deletes the table

## Files

- `CMakeLists.txt` — Build configuration
- `conanfile.txt` — Dependency management (SQLite3)
- `main.cpp` — Example CRUD operations
