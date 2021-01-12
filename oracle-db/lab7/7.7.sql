--7.7.1
select distinct
'Q' || to_char(oh.orderdate, 'q') Quarter,
c.customerkey,
c.lastname,
c.firstname
from customer c
inner join orderheader oh on c.customerkey = oh.customerkey
inner join orderchannel ch on oh.channelkey = ch.channelkey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
inner join productcategory pc on pc.productCategoryKey = psc.productCategoryKey
where pc.productCategoryName = 'Bikes'
and ch.channelname = 'Mobile application'
and to_char(oh.orderdate, 'yyyy') = '2019'
and to_char(oh.orderdate, 'q') = '1'
union
select distinct
'Q' || to_char(oh.orderdate, 'q') Quarter,
c.customerkey,
c.lastname,
c.firstname
from customer c
inner join orderheader oh on c.customerkey = oh.customerkey
inner join orderchannel ch on oh.channelkey = ch.channelkey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
inner join productcategory pc on pc.productCategoryKey = psc.productCategoryKey
where pc.productCategoryName = 'Bikes'
and ch.channelname = 'Mobile application'
and to_char(oh.orderdate, 'yyyy') = '2019'
and to_char(oh.orderdate, 'q') = '3'
order by 1, 3;

-- the rest of exercises were skipped
