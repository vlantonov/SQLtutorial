#include <soci/soci.h>
#include <iostream>

int main() {
    try {
        // soci::backend_factory const &backEnd = *soci::factory_mysql();

        // Connection parameters
        std::string connect_str = "db=test_db user=test_user password=test_pass host=127.0.0.1 port=3306";

        // Connect to MariaDB
        soci::session sql("mysql", connect_str);

        // 1. Create table
        std::cout << "Creating table ..." << std::endl;
        sql << "CREATE TABLE IF NOT EXISTS demo_table (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(50), value INT)";

        // 2. Insert data
        std::cout << "Inserting data ..." << std::endl;
        sql << "INSERT INTO demo_table (name, value) VALUES ('foo', 123), ('bar', 456)";

        // 3. Read data
        std::cout << "Reading data ..." << std::endl;
        soci::rowset<soci::row> rs = (sql.prepare << "SELECT id, name, value FROM demo_table");
        for (auto const &r : rs) {
            std::cout << "id: " << r.get<int>(0)
                      << ", name: " << r.get<std::string>(1)
                      << ", value: " << r.get<int>(2) << std::endl;
        }

        // 4. Update data
        std::cout << "Updating data ..." << std::endl;
        sql << "UPDATE demo_table SET value = value + 1 WHERE name = 'foo'";

        // 5. Read updated data
        std::cout << "Reading updated data ..." << std::endl;
        soci::rowset<soci::row> rs2 = (sql.prepare << "SELECT id, name, value FROM demo_table");
        for (auto const &r : rs2) {
            std::cout << "id: " << r.get<int>(0)
                      << ", name: " << r.get<std::string>(1)
                      << ", value: " << r.get<int>(2) << std::endl;
        }

        // 6. Delete table
        std::cout << "Dropping table ..." << std::endl;
        sql << "DROP TABLE demo_table";

        std::cout << "All operations completed successfully." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}