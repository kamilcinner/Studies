--7.8.1
select
c.customerkey,
c.lastname,
c.firstname
from customer c
inner join orderheader oh on oh.customerkey = c.customerkey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
where to_char(oh.orderdate, 'YYYY') = '2019'
and lower(p.productname) like '%mountain%'
intersect
select
c.customerkey,
c.lastname,
c.firstname
from customer c
inner join orderheader oh on oh.customerkey = c.customerkey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
where to_char(oh.orderdate, 'YYYY') = '2019'
and lower(p.productname) like '%road%'
order by 2;

--7.8.2
select
p.productname
from country c
inner join orderheader oh on oh.countrykey = c.countrykey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
where c.countryname = 'United States'
intersect
select
p.productname
from country c
inner join orderheader oh on oh.countrykey = c.countrykey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
where c.countryname = 'Canada'
order by 1;

--7.8.3
select
c.customerkey,
c.lastname,
c.firstname
from customer c
inner join orderheader oh on oh.customerkey = c.customerkey
where to_char(oh.orderdate, 'YYYY') = '2018'
intersect
select
c.customerkey,
c.lastname,
c.firstname
from customer c
inner join orderheader oh on oh.customerkey = c.customerkey
where to_char(oh.orderdate, 'YYYY') = '2019'
order by 2;

--7.8.4
select
c.countryname
from country c
inner join orderheader oh on oh.countrykey = c.countrykey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
where p.productname = 'Rear Brakes'
intersect
select
c.countryname
from country c
inner join orderheader oh on oh.countrykey = c.countrykey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
where p.productname = 'Front Brakes'
order by 1;

--7.8.5
select
pm.paymentmethodname
from paymentmethod pm
inner join orderheader oh on oh.paymentmethodkey = pm.paymentmethodkey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
inner join productcategory pc on pc.productcategorykey = psc.productcategorykey
where pc.productcategoryname = 'Bikes'
intersect
select
pm.paymentmethodname
from paymentmethod pm
inner join orderheader oh on oh.paymentmethodkey = pm.paymentmethodkey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
inner join productcategory pc on pc.productcategorykey = psc.productcategorykey
where pc.productcategoryname = 'Accessories'
order by 1;
