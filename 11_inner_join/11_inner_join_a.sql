SELECT order_id, orders.customer_id, first_name, last_name
FROM orders
-- INNER JOIN customers
JOIN customers
    ON orders.customer_id = customers.customer_id;