select distinct(N_NAME), count(C_CUSTKEY) as qtd_encomendas
from NATION
inner join CUSTOMER on NATION.N_NATIONKEY = CUSTOMER.C_NATIONKEY
inner join ORDERS on CUSTOMER.C_CUSTKEY = ORDERS.O_CUSTKEY
group by N_NAME
order by qtd_encomendas desc;