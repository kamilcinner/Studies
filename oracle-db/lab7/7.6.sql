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

-- poprawione
SELECT
 dm.deliverymethodkey,
 pc.productcategorykey
FROM deliverymethod dm CROSS JOIN productcategory pc
LEFT JOIN
 (orderheader oh
 INNER JOIN orderdetail od ON od.orderkey = oh.orderkey
 INNER JOIN product p ON p.productkey = od.productkey
 INNER JOIN productsubcategory pcs
 ON pcs.productsubcategorykey = p.productsubcategorykey)
ON dm.deliverymethodkey = oh.deliverymethodkey
 AND pcs.productcategorykey = pc.productcategorykey
WHERE oh.deliverymethodkey IS NULL
ORDER BY 1,2;

--inne rozwiazanie
select
 deliverymethodkey,
 productcategorykey
 from deliverymethod dm cross join productcategory pc
 minus
 select distinct
 oh.deliverymethodkey,
 pc.productcategorykey
 from orderheader oh inner join orderdetail od
 on oh.orderkey = od.orderkey
 inner join product p on p.productkey = od.productkey
 inner join productsubcategory pc on pc.productsubcategorykey = p.productsubcategorykey

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
