select count(*)
from (
    select C_CUSTKEY
    from CUSTOMER       
    inner join ORDERS on CUSTOMER.C_CUSTKEY = ORDERS.O_CUSTKEY
    except 
        select C_CUSTKEY
        from CUSTOMER
        inner join ORDERS on ORDERS.O_CUSTKEY = CUSTOMER.C_CUSTKEY
        where O_COMMENT
        like '%special request%' 
);