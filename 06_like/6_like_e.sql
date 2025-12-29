SELECT * 
FROM customers
WHERE (address LIKE '%trail%' OR address LIKE '%avenue%');

SELECT * 
FROM customers WHERE phone LIKE '%9';