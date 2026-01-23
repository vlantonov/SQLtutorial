USE sql_store;

SELECT 
    c.customer_id,
    c.first_name,
    o.order_id
FROM customers c
-- LEFT OUTER JOIN orders o
LEFT JOIN orders o
ON o.customer_id = c.customer_id
ORDER BY c.customer_id;