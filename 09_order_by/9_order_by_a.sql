USE sql_store;
SELECT * 
FROM customers
-- ORDER BY first_name;
-- ORDER BY first_name DESC;
ORDER BY state DESC, first_name ASC;