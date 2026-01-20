SELECT 
    p.date,
    p.invoice_id,
    p.amount,
    c.name,
    pm.name
FROM sql_invoicing.payments p
JOIN sql_invoicing.clients c
    ON p.client_id = c.client_id
JOIN sql_invoicing.payment_methods pm
    ON p.payment_method = pm.payment_method_id;