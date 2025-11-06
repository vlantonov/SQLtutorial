# C++ MariaDB CRUD Project

This project demonstrates a minimal C++ application that connects to a MariaDB server, creates a table, performs CRUD operations (Create, Read, Update, Delete), and deletes the table. It uses CMake for building, Conan for dependency management, and Docker Compose to spin up a MariaDB server for local development and testing.

## Features

- Connects to MariaDB using the `mariadb-connector-c` library.
- Demonstrates table creation, data insertion, reading, updating, and deletion.
- Uses Docker Compose for easy local MariaDB database setup.

## Prerequisites

- [CMake](https://cmake.org/) (>= 3.21)
- [Conan](https://conan.io/) (>= 2.0)
- [Docker](https://www.docker.com/) & [Docker Compose](https://docs.docker.com/compose/)

## Getting Started

Using `build` folder

### Debug build
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

### Release build
```sh
conan install .. --build=missing -pr:b=default -s build_type=Release
cmake .. --preset conan-release
cd Release
make
```

### Run the Application

```bash
./mariadb_crud_example
```

## Configuration

The default database connection parameters are:

- Host: `127.0.0.1`
- Port: `3306`
- Username: `test_user`
- Password: `test_pass`
- Database: `test_db`

These are set in `main.cpp`. Ensure they match your database configuration.

