#include <iostream>
#include <mariadb/conncpp.hpp>
#include <stdexcept>
#include <string>
#include <vector>

void createTable(std::unique_ptr<sql::Connection>& conn) {
  const char* sql =
      "CREATE TABLE IF NOT EXISTS users ("
      "id INT PRIMARY KEY AUTO_INCREMENT,"
      "name VARCHAR(100),"
      "age INT"
      ")";
  // Create a new PreparedStatement
  std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement(sql));

  // Execute query
  stmnt->executeQuery();

  std::cout << "Table created.\n";
}

void insertUser(std::unique_ptr<sql::Connection>& conn, const std::string& name,
                int age) {
  // Create a new PreparedStatement
  std::unique_ptr<sql::PreparedStatement> stmnt(
      conn->prepareStatement("INSERT INTO users(name, age) VALUES(?,?)"));

  // Bind values to SQL statement
  stmnt->setString(1, name);
  stmnt->setInt(2, age);

  // Execute query
  stmnt->executeQuery();

  std::cout << "Inserted user: " << name << "\n";
}

void readUsers(std::unique_ptr<sql::Connection>& conn) {
  const char* sql = "SELECT id, name, age FROM users";
  std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement(sql));

  std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery());

  while (res->next()) {
    int id = res->getInt("id");
    auto name = res->getString("name");
    int age = res->getInt("age");
    std::cout << "ID: " << id << ", Name: " << name << ", Age: " << age << "\n";
  }
}

void updateUser(std::unique_ptr<sql::Connection>& conn, int id,
                const std::string& name, int age) {
  // Create a new PreparedStatement
  std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement(
      "UPDATE users SET name = ?, age = ? WHERE id = ?"));

  // Bind values to SQL statement
  stmnt->setString(1, name);
  stmnt->setInt(2, age);
  stmnt->setInt(3, id);

  // Execute query
  stmnt->executeQuery();

  std::cout << "Updated user ID: " << id << "\n";
}

void deleteTable(std::unique_ptr<sql::Connection>& conn) {
  const char* sql = "DROP TABLE IF EXISTS users";
  std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement(sql));

  stmnt->executeQuery();

  std::cout << "Table deleted.\n";
}

int main() {
  // Instantiate Driver
  sql::Driver* driver = sql::mariadb::get_driver_instance();

  // Configure Connection
  sql::SQLString url("jdbc:mariadb://localhost:3306/test_db");
  sql::Properties properties(
      {{"user", "test_user"}, {"password", "test_pass"}});

  // Establish Connection
  std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

  createTable(conn);

  // Insert users
  insertUser(conn, "Alice", 30);
  insertUser(conn, "Bob", 25);

  readUsers(conn);

  // Update user
  updateUser(conn, 1, "Alice Smith", 31);

  readUsers(conn);

  deleteTable(conn);

  return 0;
}