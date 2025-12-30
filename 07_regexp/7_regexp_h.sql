SELECT * 
FROM customers
-- WHERE first_name REGEXP 'Elka|Ambur';
-- WHERE last_name REGEXP 'ey$|on$';
-- WHERE last_name REGEXP '^My|se';
WHERE last_name REGEXP 'b[ru]';