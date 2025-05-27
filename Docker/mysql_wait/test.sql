DROP DATABASE IF EXISTS `test_db`;
CREATE DATABASE `test_db`; 
USE `test_db`;

CREATE TABLE IF NOT EXISTS users (
  id INT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(100),
  age INT
);

INSERT INTO users(name, age) VALUES("test_name", 13);
