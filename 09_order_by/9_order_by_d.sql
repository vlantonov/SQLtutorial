USE sql_store;
SELECT *, unit_price * quantity AS total_price
FROM order_items
WHERE order_id = 2
ORDER BY total_price DESC;