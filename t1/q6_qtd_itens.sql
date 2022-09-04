select N_NAME, sum(L_QUANTITY) as qtd_itens 
from NATION 
inner join CUSTOMER on NATION.N_NATIONKEY = CUSTOMER.C_NATIONKEY
inner join ORDERS on CUSTOMER.C_CUSTKEY = ORDERS.O_CUSTKEY 
inner join LINEITEM on ORDERS.O_ORDERKEY = LINEITEM.L_ORDERKEY
group by N_NAME
order by qtd_itens desc
limit 10;