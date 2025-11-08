# Boost.MySQL Demo Project

A demonstration project showing how to use Boost.MySQL library for database operations with MariaDB/MySQL.

## Overview

This project demonstrates basic database operations using Boost.MySQL:
- Creating tables
- Inserting data
- Reading data
- Updating records
- Deleting tables

## Prerequisites

- C++20 compatible compiler
- CMake 3.15 or higher
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
conan install .. --build=missing -pr:b=default -s build_type=Debug
```

### 3. Configure CMake

```bash
cmake .. --preset conan-debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```

### 4. Build the Project

```bash
cd Debug
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

Or update the connection parameters in `main.cpp`:

```cpp
mysql::handshake_params params(
    "your_username",    // username
    "your_password",    // password
    "your_database"     // database
);
```

And the resolver endpoint:

```cpp
auto endpoints = resolver.resolve("your_host", "your_port");
```

## Running the Application

```bash
./build/mysql_demo
```

### Expected Output

```
Creating table ...
Inserting data ...
Reading data ...
id: 1, name: foo, value: 123
id: 2, name: bar, value: 456
Updating data ...
Reading updated data ...
id: 1, name: foo, value: 124
id: 2, name: bar, value: 456
Dropping table ...
All operations completed successfully.
```

## Configuration

Default connection parameters:
- **Host**: 127.0.0.1
- **Port**: 3306
- **Database**: test_db
- **Username**: test_user
- **Password**: test_pass

## Build the image
docker build -t boost-mysql-demo .

## Run with external MySQL/MariaDB
docker run --rm \
  -e DB_HOST=your_host \
  -e DB_PORT=3306 \
  -e DB_NAME=test_db \
  -e DB_USER=test_user \
  -e DB_PASS=test_pass \
  --network=host \
  boost-mysql-demo

## Troubleshooting

### Connection Errors

If you encounter connection errors:
1. Verify MySQL/MariaDB is running: `systemctl status mysql`
2. Check firewall settings allow port 3306
3. Verify user credentials and permissions
4. Ensure the database exists

## References

- [Boost.MySQL Documentation](https://www.boost.org/doc/libs/release/libs/mysql/doc/html/index.html)
- [Boost.Asio Documentation](https://www.boost.org/doc/libs/release/doc/html/boost_asio.html)
- [Conan Documentation](https://docs.conan.io/)
- [CMake Documentation](https://cmake.org/documentation/)
