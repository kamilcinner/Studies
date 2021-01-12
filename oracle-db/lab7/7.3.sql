--7.3.1
select distinct
c.customerKey,
c.firstname,
c.lastname
from customer c left join orderHeader oh on c.customerKey = oh.customerKey
where oh.customerKey is null;

--7.3.2
select distinct
pm.paymentmethodname
from orderheader oh
right join paymentmethod pm on oh.paymentmethodkey = pm.paymentmethodkey
where oh.paymentmethodkey is null;

--7.3.3
select distinct
c.countryname
from country c
left join orderheader oh on oh.countrykey = c.countrykey
where oh.countrykey is null
order by 1;

--7.3.4
select distinct
p.productcode,
p.productname
from product p
left join orderdetail od on p.productkey = od.productkey
where od.productkey is null
order by 1;
