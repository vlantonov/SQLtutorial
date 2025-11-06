#include <sqlite3.h>

#include <iostream>
#include <string>

void check(int rc, char const* msg) {
  if (rc != SQLITE_OK && rc != SQLITE_DONE && rc != SQLITE_ROW) {
    std::cerr << msg << ": " << sqlite3_errstr(rc) << std::endl;
    exit(1);
  }
}

int main() {
  sqlite3* db{};
  int rc = sqlite3_open(":memory:", &db);

  // https://sqlite.org/c3ref/open.html
  // int rc = sqlite3_open("example.db", &db);

  check(rc, "Cannot open database");

  // 1. Create Table
  const char* create_sql =
      "CREATE TABLE users (id INTEGER PRIMARY KEY, name TEXT);";
  rc = sqlite3_exec(db, create_sql, nullptr, nullptr, nullptr);
  check(rc, "Failed to create table");

  // 2. Insert/Update data
  const char* insert_sql = "INSERT INTO users (name) VALUES (?);";
  sqlite3_stmt* stmt;
  rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, nullptr);
  check(rc, "Failed to prepare insert");

  std::string name = "Alice";
  sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);
  check(rc, "Failed to insert data");
  sqlite3_finalize(stmt);

  // 3. Read data
  std::cout << "Users in DB:" << std::endl;
  const char* select_sql = "SELECT id, name FROM users;";
  rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, nullptr);
  check(rc, "Failed to prepare select");
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char* uname = sqlite3_column_text(stmt, 1);
    std::cout << "ID: " << id << ", Name: " << uname << std::endl;
  }
  check(rc == SQLITE_DONE ? SQLITE_OK : rc, "Failed to read data");
  sqlite3_finalize(stmt);

  // 4. Update data
  const char* update_sql = "UPDATE users SET name = ? WHERE id = 1;";
  rc = sqlite3_prepare_v2(db, update_sql, -1, &stmt, nullptr);
  check(rc, "Failed to prepare update");
  std::string new_name = "Bob";
  sqlite3_bind_text(stmt, 1, new_name.c_str(), -1, SQLITE_STATIC);
  rc = sqlite3_step(stmt);
  check(rc, "Failed to update data");
  sqlite3_finalize(stmt);

  // Show updated data
  std::cout << "After update:" << std::endl;
  rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, nullptr);
  check(rc, "Failed to prepare select");
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char* uname = sqlite3_column_text(stmt, 1);
    std::cout << "ID: " << id << ", Name: " << uname << std::endl;
  }
  check(rc == SQLITE_DONE ? SQLITE_OK : rc, "Failed to read data");
  sqlite3_finalize(stmt);

  // 5. Delete table
  const char* drop_sql = "DROP TABLE users;";
  rc = sqlite3_exec(db, drop_sql, nullptr, nullptr, nullptr);
  check(rc, "Failed to drop table");

  sqlite3_close(db);
  std::cout << "Finished SQL operations!" << std::endl;
  return 0;
}