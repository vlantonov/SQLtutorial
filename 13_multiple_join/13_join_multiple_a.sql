SELECT
    o.order_id,
    o.order_date,
    c.first_name,
    c.last_name,
    os.name
FROM sql_store.orders o
JOIN sql_store.customers c
    ON o.customer_id = c.customer_id
JOIN sql_store.order_statuses os
    ON o.status = os.order_status_id;