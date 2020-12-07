--7.6.1
select
c.countryname as "Country",
ch.channelname as "Channel"
from country c
cross join orderchannel ch
left join orderheader oh
on c.countrykey = oh.countrykey
and ch.channelkey = oh.channelkey
where oh.orderkey is null
order by 1;

--7.6.2
select distinct
pc.productcategoryname as "Product category",
dm.deliverymethodname as "Delivery method"
from productcategory pc
cross join deliverymethod dm
left join productsubcategory psc
on pc.productcategorykey = psc.productcategorykey
left join product p
on p.productsubcategorykey = psc.productsubcategorykey
left join orderdetail od
on p.productkey = od.productkey
left join orderheader oh
on oh.orderkey = od.orderkey
where oh.orderkey is null
order by 1, 2;
-- chyba do poprawy

--7.6.3
select distinct
c.customerkey,
c.lastname,
c.firstname
from customer c
cross join paymentmethod pm
left join orderheader oh
on oh.customerkey = c.customerkey
and oh.paymentmethodkey = pm.paymentmethodkey
where pm.paymentmethodname = 'PayPal'
and oh.orderkey is null
order by 2;

--7.6.3
select distinct
c.customerkey,
c.lastname,
c.firstname
from productcategory pc
cross join customer c
left join productsubcategory psc
on pc.productcategorykey = psc.productcategorykey
left join product p
on p.productsubcategorykey = psc.productsubcategorykey
left join orderdetail od
on p.productkey = od.productkey
left join orderheader oh
on oh.orderkey = od.orderkey
and oh.customerkey = c.customerkey
where pc.productcategoryName = 'Bikes'
and oh.orderkey is null
order by 2;
-- chyba do poprawy
