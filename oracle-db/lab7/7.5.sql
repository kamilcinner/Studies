--7.5.1
select distinct
pm.paymentmethodname,
dm.deliverymethodname
from deliverymethod dm
full join orderheader oh
on dm.deliverymethodkey = oh.deliverymethodkey
full join paymentmethod pm
on oh.paymentmethodkey = pm.paymentmethodkey
where oh.paymentmethodkey is null
and oh.deliverymethodkey is null
order by 1;

--7.5.2
select distinct
p.productname as "Product",
c.countryname as "Country"
from orderheader oh
inner join orderdetail od
on oh.orderkey = od.orderkey
full join product p
on p.productkey = od.productkey
full join country c
on c.countrykey = oh.countrykey
where oh.countrykey is null
and od.productkey is null
order by 1;

--7.5.3
select distinct
c.customerkey,
c.lastname,
c.firstname,
ch.channelname
from orderheader oh
full join customer c
on oh.customerkey = c.customerkey
full join orderchannel ch
on oh.channelkey = ch.channelkey
where oh.customerkey is null
and oh.channelkey is null
order by 2, 3;
