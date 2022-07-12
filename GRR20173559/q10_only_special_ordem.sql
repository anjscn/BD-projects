select count(*)
from (
    select C_CUSTKEY
    from CUSTOMER
    inner join ORDERS on ORDERS.O_CUSTKEY = CUSTOMER.C_CUSTKEY
    where O_COMMENT
    like '%special request%'
    except
        select C_CUSTKEY        
        from CUSTOMER
        inner join ORDERS on ORDERS.O_CUSTKEY = CUSTOMER.C_CUSTKEY
        where O_COMMENT
        like '%unusual package%'
);