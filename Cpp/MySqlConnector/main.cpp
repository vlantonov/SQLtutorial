// Based on:
// https://stackoverflow.com/questions/16424828/how-to-connect-mysql-database-using-c
// Posted by hd1
// Retrieved 2025-11-08, License - CC BY-SA 4.0

// Standard C++ includes
#include <stdlib.h>

#include <iostream>
#include <memory>

//  Include directly the different
//  headers from cppconn/ and mysql_driver.h + mysql_util.h
//  (and mysql_connection.h). This will reduce your build time!
//  sudo apt-get install libmysqlcppconn-dev
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "mysql_connection.h"

using namespace std;

void create_table(sql::Connection* conn) {
  const char* sql =
      "CREATE TABLE IF NOT EXISTS users ("
      "id INT PRIMARY KEY AUTO_INCREMENT,"
      "name VARCHAR(100),"
      "age INT"
      ")";
  std::unique_ptr<sql::Statement> stmt{conn->createStatement()};
  bool result = stmt->execute(sql);
  std::cout << "Table created: " << result << "\n";
}

void insert_user(sql::Connection* conn, const std::string& name, int age) {
  std::string sql = "INSERT INTO users(name, age) VALUES('" + name + "'," +
                    std::to_string(age) + ")";
  std::unique_ptr<sql::Statement> stmt{conn->createStatement()};
  bool result = stmt->execute(sql);
  std::cout << "Inserted user: " << name << "  result: " << result << "\n";
}

void read_users(sql::Connection* conn) {
  const char* sql = "SELECT id, name, age FROM users";
  std::unique_ptr<sql::Statement> stmt{conn->createStatement()};
  std::unique_ptr<sql::ResultSet> res{stmt->executeQuery(sql)};
  while (res->next()) {
    int id = res->getInt("id");
    std::string name = res->getString("name");
    int age = res->getInt("age");
    std::cout << "User: ID=" << id << ", Name=" << name << ", Age=" << age
              << "\n";
  }
}

void update_user(sql::Connection* conn, int id, const std::string& new_name,
                 int new_age) {
  std::string sql = "UPDATE users SET name='" + new_name +
                    "', age=" + std::to_string(new_age) +
                    " WHERE id=" + std::to_string(id);
  std::unique_ptr<sql::Statement> stmt{conn->createStatement()};
  bool result = stmt->executeUpdate(sql);
  std::cout << "Updated user ID: " << id << "  result: " << result << "\n";
}

void delete_table(sql::Connection* conn) {
  const char* sql = "DROP TABLE IF EXISTS users";
  std::unique_ptr<sql::Statement> stmt{conn->createStatement()};
  bool result = stmt->execute(sql);
  std::cout << "Table deleted: " << result << "\n";
}

int main(void) {
  cout << "Start connection" << endl;

  try {
    // Create a connection
    sql::Driver* driver = get_driver_instance();
    std::unique_ptr<sql::Connection> con{
        driver->connect("tcp://127.0.0.1:3306", "test_user", "test_pass")};

    // Connect to the MySQL test database
    con->setSchema("test_db");

    create_table(con.get());

    insert_user(con.get(), "Alice", 30);
    insert_user(con.get(), "Bob", 25);

    read_users(con.get());

    update_user(con.get(), 1, "Alice Smith", 31);

    read_users(con.get());

    delete_table(con.get());

  } catch (sql::SQLException& e) {
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
  }

  cout << endl;

  return EXIT_SUCCESS;
}
