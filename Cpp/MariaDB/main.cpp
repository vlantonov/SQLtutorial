#include <mariadb/mysql.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#define HOST "127.0.0.1"
#define USER "test_user"
#define PASS "test_pass"
#define DB "test_db"
#define PORT 3306

void check_connection(MYSQL* conn) {
  if (!conn) {
    throw std::runtime_error("mysql_init() failed (out of memory?)");
  }
  if (!mysql_real_connect(conn, HOST, USER, PASS, DB, PORT, nullptr, 0)) {
    std::string err = mysql_error(conn);
    mysql_close(conn);
    throw std::runtime_error("mysql_real_connect() failed: " + err);
  }
}

void execute(MYSQL* conn, const char* sql) {
  if (mysql_query(conn, sql)) {
    std::string err = mysql_error(conn);
    throw std::runtime_error(std::string("MySQL query error: ") + err +
                             "\nSQL: " + sql);
  }
}

void create_table(MYSQL* conn) {
  const char* sql =
      "CREATE TABLE IF NOT EXISTS users ("
      "id INT PRIMARY KEY AUTO_INCREMENT,"
      "name VARCHAR(100),"
      "age INT"
      ")";
  execute(conn, sql);
  std::cout << "Table created.\n";
}

void insert_user(MYSQL* conn, const std::string& name, int age) {
  std::string sql = "INSERT INTO users(name, age) VALUES('" + name + "'," +
                    std::to_string(age) + ")";
  execute(conn, sql.c_str());
  std::cout << "Inserted user: " << name << "\n";
}

void read_users(MYSQL* conn) {
  const char* sql = "SELECT id, name, age FROM users";
  if (mysql_query(conn, sql)) {
    std::cerr << "SELECT failed: " << mysql_error(conn) << "\n";
    return;
  }
  MYSQL_RES* result = mysql_store_result(conn);
  if (!result) {
    std::cerr << "mysql_store_result() failed: " << mysql_error(conn) << "\n";
    return;
  }
  MYSQL_ROW row;
  std::cout << "Users in table:\n";
  while ((row = mysql_fetch_row(result))) {
    std::cout << "id: " << row[0] << ", name: " << row[1] << ", age: " << row[2]
              << "\n";
  }
  mysql_free_result(result);
}

void update_user(MYSQL* conn, int id, const std::string& new_name,
                 int new_age) {
  std::string sql = "UPDATE users SET name='" + new_name +
                    "', age=" + std::to_string(new_age) +
                    " WHERE id=" + std::to_string(id);
  execute(conn, sql.c_str());
  std::cout << "Updated user id: " << id << "\n";
}

void delete_table(MYSQL* conn) {
  const char* sql = "DROP TABLE IF EXISTS users";
  execute(conn, sql);
  std::cout << "Table deleted.\n";
}

int main() {
  MYSQL* conn = mysql_init(nullptr);
  try {
    check_connection(conn);

    // Create table
    create_table(conn);

    // Insert users
    insert_user(conn, "Alice", 30);
    insert_user(conn, "Bob", 25);

    // Read users
    read_users(conn);

    // Update user
    update_user(conn, 1, "Alice Smith", 31);

    // Read users again
    read_users(conn);

    // Delete the table
    delete_table(conn);

    mysql_close(conn);
    return 0;
  } catch (const std::exception& ex) {
    std::cerr << ex.what() << "\n";
    if (conn) mysql_close(conn);
    return 1;
  }
}