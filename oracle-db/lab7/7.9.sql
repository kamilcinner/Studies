--7.9.1
select distinct
c.customerkey,
c.lastname,
c.firstname
from customer c
inner join orderheader oh on oh.customerkey = c.customerkey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
where psc.productsubcategoryname = 'Mountain Bikes'
minus
select distinct
c.customerkey,
c.lastname,
c.firstname
from customer c
inner join orderheader oh on oh.customerkey = c.customerkey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
where p.productname = 'Mountain Tire'
order by 2;

--7.9.2
select distinct
c.customerkey,
c.lastname,
c.firstname
from customer c
inner join orderheader oh on oh.customerkey = c.customerkey
inner join orderchannel ch on ch.channelkey = oh.channelkey
where ch.channelname = 'Mobile Application'
minus
select distinct
c.customerkey,
c.lastname,
c.firstname
from customer c
inner join orderheader oh on oh.customerkey = c.customerkey
inner join orderchannel ch on ch.channelkey = oh.channelkey
where ch.channelname != 'Mobile Application'
order by 2;

--7.9.3
select
c.countryname,
pm.paymentmethodname
from country c
cross join paymentmethod pm
minus
select distinct
c.countryname,
pm.paymentmethodname
from country c
inner join orderheader oh on oh.countrykey = c.countrykey
inner join paymentmethod pm on pm.paymentmethodkey = oh.paymentmethodkey
order by 1;

--7.9.4
select distinct
c.countryname
from orderheader oh
inner join country c on c.countrykey = oh.countrykey
minus
select distinct
c.countryname
from customer cu
inner join city ci on ci.citykey = cu.citykey
inner join country c on cu.countrykey = ci.countrykey
order by 1;

--7.9.5
select distinct
p.productname
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
where to_char(oh.orderdate, 'YYYY') = '2018'
minus
select distinct
p.productname
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
where to_char(oh.orderdate, 'YYYY') = '2019'
order by 1;

--7.9.6
select
y.year Year,
c.countryname,
p.productname
from country c
cross join product p
cross join (
    select distinct extract(year from orderdate) year from orderheader
) y
minus
select distinct
extract(year from oh.orderdate) Year,
c.countryname,
p.productname
from orderheader oh
inner join country c on c.countrykey = oh.countrykey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
order by 1, 2, 3;
