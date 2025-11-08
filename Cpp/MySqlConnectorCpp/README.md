# mysql-concpp-example

A minimal example that demonstrates building and running a program that links against
mysql-connector-cpp (installed via Conan) using CMake and C++20.

## Overview

This project demonstrates basic database operations using Boost.MySQL:
- Creating tables
- Inserting data
- Reading data
- Updating records
- Deleting tables

## Prerequisites

- C++20 compatible compiler
- CMake 3.28 or higher
- Conan package manager
- MariaDB or MySQL server running locally

## Dependencies

- Boost 1.84.0 (includes Boost.MySQL, Boost.Asio, and Boost.System)
- Threads library

## Project Structure

```
boost-mysql-demo/
├── conanfile.txt       # Conan dependencies
├── CMakeLists.txt      # CMake build configuration
├── main.cpp            # Main application code
└── README.md           # This file
```

## Building the Project

### 1. Install Conan (if not already installed)

```bash
pip install conan
```

### 2. Install Dependencies

```bash
conan install .. --build=missing -pr:b=default -s build_type=Release
```

### 3. Configure CMake

```bash
cmake .. --preset conan-release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```

### 4. Build the Project

```bash
cd Release
make
```

## Database Setup

Before running the application, ensure you have a MySQL/MariaDB server running with the following configuration:

```sql
CREATE DATABASE test_db;
CREATE USER 'test_user'@'localhost' IDENTIFIED BY 'test_pass';
GRANT ALL PRIVILEGES ON test_db.* TO 'test_user'@'localhost';
FLUSH PRIVILEGES;
```

## Running the Application

```bash
./build/mysql_concpp_example
```

### Expected Output

```
Creating session
Session accepted, creating collection...
Inserting documents...
- added doc with id: 0000690f78800000000000000005
- added doc with id: 0000690f78800000000000000006
- added doc with id: 0000690f78800000000000000007
- added doc with id: 0000690f78800000000000000008
Fetching documents...
doc#0: {"_id": "0000690f78800000000000000006", "age": 2, "name": "bar", "toys": ["car", "ball"]}
 field `_id`: 0000690f78800000000000000006
 field `age`: 2
 field `name`: bar
 field `toys`: ["car", "ball"]
 name: bar
- toys:
  car
  ball

doc#1: {"_id": "0000690f78800000000000000007", "age": 2, "name": "bar", "toys": ["car", "ball"]}
 field `_id`: 0000690f78800000000000000007
 field `age`: 2
 field `name`: bar
 field `toys`: ["car", "ball"]
 name: bar
- toys:
  car
  ball

doc#2: {"_id": "0000690f78800000000000000008", "age": 3, "date": {"day": 20, "month": "Apr"}, "name": "baz"}
 field `_id`: 0000690f78800000000000000008
 field `age`: 3
 field `date`: {"day": 20, "month": "Apr"}
 field `name`: baz
 name: baz
- date field
  date `day`: 20
  date `month`: Apr
  month: Apr
  day: 20

Done!
```

## Configuration

Default connection parameters:
- **Host**: 127.0.0.1
- **Port**: 33060
- **Database**: test_db
- **Username**: test_user
- **Password**: test_pass

## Build the image
docker build -t boost-mysql-demo .

## Run with external MySQL/MariaDB
docker run --rm \
  -e DB_HOST=your_host \
  -e DB_PORT=33060 \
  -e DB_NAME=test_db \
  -e DB_USER=test_user \
  -e DB_PASS=test_pass \
  --network=host \
  boost-mysql-demo

## Troubleshooting

### Connection Errors

If you encounter connection errors:
1. Verify MySQL/MariaDB is running: `systemctl status mysql`
2. Check firewall settings allow port 33060
3. Verify user credentials and permissions
4. Ensure the database exists

## References

- [MySQL Connector/C++ Documentation](https://dev.mysql.com/doc/dev/connector-cpp/latest/)
- <https://github.com/mysql/mysql-connector-cpp/>
- [Conan Documentation](https://docs.conan.io/)
- [CMake Documentation](https://cmake.org/documentation/)
