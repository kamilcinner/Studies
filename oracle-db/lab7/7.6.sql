--7.6.1
select
c.countryname as "Country",
ch.channelname as "Channel"
from country c
cross join orderchannel ch
left join orderheader oh on c.countrykey = oh.countrykey
and ch.channelkey = oh.channelkey
where oh.orderkey is null
order by 1;

--7.6.2
select
dm.deliverymethodkey,
pc.productcategorykey
from deliverymethod dm
cross join productcategory pc
left join (
    orderheader oh
    inner join orderdetail od on od.orderkey = oh.orderkey
    inner join product p on p.productkey = od.productkey
    inner join productsubcategory pcs on pcs.productsubcategorykey = p.productsubcategorykey
)
on dm.deliverymethodkey = oh.deliverymethodkey
and pcs.productcategorykey = pc.productcategorykey
where oh.orderkey is null
order by 1, 2;

-- other solution
select
deliverymethodkey,
productcategorykey
from deliverymethod dm
cross join productcategory pc
minus
select distinct
oh.deliverymethodkey,
psc.productcategorykey
from orderheader oh
inner join orderdetail od on oh.orderkey = od.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey;

--7.6.3
select
c.customerkey,
c.lastname,
c.firstname
from customer c
cross join paymentmethod pm
left join orderheader oh on oh.customerkey = c.customerkey
and oh.paymentmethodkey = pm.paymentmethodkey
where pm.paymentmethodname = 'PayPal'
and oh.orderkey is null
order by 2;

--7.6.4
select
c.customerkey,
c.lastname,
c.firstname
from productcategory pc
cross join customer c
left join (
    orderheader oh
    inner join orderdetail od on od.orderkey = oh.orderkey
    inner join product p on p.productkey = od.productkey
    inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
)
on oh.customerkey = c.customerkey
and psc.productcategorykey = pc.productcategorykey
where pc.productcategoryName = 'Bikes'
and oh.orderkey is null
order by 2;
