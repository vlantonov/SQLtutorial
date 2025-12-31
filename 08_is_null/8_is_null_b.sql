USE sql_store;
SELECT * 
FROM orders
WHERE shipped_date IS NULL;