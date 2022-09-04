select count(C_CUSTKEY)
from (
    select C_CUSTKEY
    from CUSTOMER
    except
        select C_CUSTKEY
        from CUSTOMER
        inner join ORDERS on CUSTOMER.C_CUSTKEY = ORDERS.O_CUSTKEY
);