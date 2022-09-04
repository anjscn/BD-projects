select count(C_CUSTKEY)
from (
    select C_CUSTKEY
    from CUSTOMER
    inner join ORDERS on ORDERS.O_CUSTKEY = CUSTOMER.C_CUSTKEY
    where O_COMMENT
    like '%special request%' 
    intersect
        select C_CUSTKEY
        from CUSTOMER
        inner join ORDERS on ORDERS.O_CUSTKEY = CUSTOMER.C_CUSTKEY 
        where O_COMMENT                                           
        not like '%unusual package%'
);