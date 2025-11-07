#include <boost/asio/io_context.hpp>
#include <boost/mysql.hpp>
#include <iostream>

namespace mysql = boost::mysql;

int main() {
  try {
    // Create I/O context
    boost::asio::io_context ctx;

    // The SSL context, required to establish TLS connections.
    // The default SSL options are good enough for us at this point.
    boost::asio::ssl::context ssl_ctx(boost::asio::ssl::context::tls_client);

    // Create connection
    boost::mysql::tcp_ssl_connection conn(ctx.get_executor(), ssl_ctx);

    // Connection parameters
    mysql::handshake_params params("test_user",  // username
                                   "test_pass",  // password
                                   "test_db"     // database
    );

    // Resolver and endpoint
    boost::asio::ip::tcp::resolver resolver(ctx);
    auto endpoints = resolver.resolve("127.0.0.1", "3306");

    // Connect to MariaDB
    boost::asio::ip::tcp::endpoint ep = *endpoints.begin();
    conn.connect(ep, params);

    // 1. Create table
    std::cout << "Creating table ..." << std::endl;
    mysql::results result;
    conn.execute(
        "CREATE TABLE IF NOT EXISTS demo_table "
        "(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(50), value INT)",
        result);

    // 2. Insert data
    std::cout << "Inserting data ..." << std::endl;
    conn.execute(
        "INSERT INTO demo_table (name, value) VALUES ('foo', 123), ('bar', "
        "456)",
        result);

    // 3. Read data
    std::cout << "Reading data ..." << std::endl;
    conn.execute("SELECT id, name, value FROM demo_table", result);

    for (const mysql::row_view& row : result.rows()) {
      std::cout << "id: " << row[0].as_int64()
                << ", name: " << row[1].as_string()
                << ", value: " << row[2].as_int64() << std::endl;
    }

    // 4. Update data
    std::cout << "Updating data ..." << std::endl;
    conn.execute("UPDATE demo_table SET value = value + 1 WHERE name = 'foo'",
                 result);

    // 5. Read updated data
    std::cout << "Reading updated data ..." << std::endl;
    conn.execute("SELECT id, name, value FROM demo_table", result);

    for (const mysql::row_view& row : result.rows()) {
      std::cout << "id: " << row[0].as_int64()
                << ", name: " << row[1].as_string()
                << ", value: " << row[2].as_int64() << std::endl;
    }

    // 6. Delete table
    std::cout << "Dropping table ..." << std::endl;
    conn.execute("DROP TABLE demo_table", result);

    // Close connection
    conn.close();

    std::cout << "All operations completed successfully." << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
