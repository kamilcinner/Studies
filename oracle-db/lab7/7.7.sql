--7.7.1
select distinct
case
    when to_char(oh.orderdate, 'mm') <= 3 then 'Q1'
    when to_char(oh.orderdate, 'mm') in ('07', '08', '09') then 'Q3'
end as "Quarter",
c.customerkey,
c.lastname,
c.firstname
from customer c
inner join orderheader oh
on c.customerkey = oh.customerkey
inner join orderchannel ch
on oh.channelkey = ch.channelkey
inner join orderdetail od
on od.orderkey = oh.orderkey
inner join product p
on p.productkey = od.productkey
inner join productsubcategory psc
on psc.productsubcategorykey = p.productsubcategorykey
inner join productcategory pc
on pc.productCategoryKey = psc.productCategoryKey
where pc.productCategoryName = 'Bikes'
and ch.channelname = 'Mobile Application'
and to_char(oh.orderdate, 'YYYY') = '2019'
order by 1, 2;