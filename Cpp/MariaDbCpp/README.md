# MariaDB C++ Connector Example

A simple C++ application demonstrating CRUD (Create, Read, Update, Delete) operations using the MariaDB C++ Connector.

## Overview

This project showcases how to interact with a MariaDB database using the official MariaDB C++ Connector library. It includes examples of:

- Creating database tables
- Inserting records
- Reading/querying data
- Updating existing records
- Deleting tables

## Prerequisites

- C++20 compatible compiler
- CMake 3.21 or higher
- Conan package manager
- MariaDB server instance
- MariaDB C++ Connector library

## Database Setup

Before running the application, ensure you have a MariaDB server running with the following configuration:

```sql
CREATE DATABASE test_db;
CREATE USER 'test_user'@'localhost' IDENTIFIED BY 'test_pass';
GRANT ALL PRIVILEGES ON test_db.* TO 'test_user'@'localhost';
FLUSH PRIVILEGES;
```

## Project Structure

```
.
├── main.cpp          # Main application code with CRUD operations
├── CMakeLists.txt    # CMake build configuration
├── conanfile.txt     # Conan dependencies
└── README.md         # This file
```

## Dependencies

The project uses Conan to manage the following dependencies:

- `mariadb-connector-cpp/1.1.4` - MariaDB C++ Connector
- `libcurl/8.12.1` - Required by the connector

## Building the Project

### 1. Install Dependencies with Conan

```bash
conan install . --output-folder=build --build=missing
```

### 2. Configure with CMake

```bash
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
```

### 3. Build

```bash
cmake --build .
```

## Running the Application

After building, run the executable:

```bash
./mariadb_cpp_example
```

### Expected Output

```
Table created.
Inserted user: Alice
Inserted user: Bob
ID: 1, Name: Alice, Age: 30
ID: 2, Name: Bob, Age: 25
Updated user ID: 1
ID: 1, Name: Alice Smith, Age: 31
ID: 2, Name: Bob, Age: 25
Table deleted.
```

## Configuration

To connect to a different database, modify the connection parameters in `main.cpp`:

```cpp
sql::SQLString url("jdbc:mariadb://hostname:port/database_name");
sql::Properties properties({{"user", "your_user"}, {"password", "your_password"}});
```

## Error Handling

The current implementation assumes successful database operations. For production use, consider adding try-catch blocks around database operations to handle potential exceptions:

```cpp
try {
    insert_user(conn, "Alice", 30);
} catch (sql::SQLException& e) {
    std::cerr << "SQL Error: " << e.what() << std::endl;
}
```

## License

This is example code for educational purposes.

## References

- [MariaDB C++ Connector Documentation](https://mariadb.com/kb/en/mariadb-connector-cpp/)
- [How to Connect C++ Programs to MariaDB](https://mariadb.com/resources/blog/how-to-connect-c-programs-to-mariadb/)
- [MariaDB Connector/C++ Sample Application](https://mariadb.com/docs/connectors/mariadb-connector-cpp/mariadb-connector-cpp-sample-application)
- [Conan Package Manager](https://conan.io/)
- [CMake Documentation](https://cmake.org/documentation/)