--1
select
to_char(oh.orderdate, 'yyyy') Year,
coalesce(to_char(oh.orderdate, 'mm'), 'Year total') Month,
sum(od.quantity * od.transactionprice) Total
from orderheader oh
inner join orderdetail od on oh.orderkey = od.orderkey
group by to_char(oh.orderdate, 'yyyy'),
rollup(to_char(oh.orderdate, 'mm'))
order by 1, 2 nulls first;

--2
select
pc.productcategoryname as "Product category",
to_char(oh.orderdate, 'yyyy') as "Year",
sum(od.quantity * od.transactionprice) Total
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
inner join productcategory pc on pc.productcategorykey = psc.productcategorykey
group by cube(
    pc.productcategoryname,
    to_char(oh.orderdate, 'yyyy')
)
order by 1 nulls first, 2 nulls first;

--3
select
c.countryname as "Country",
to_char(oh.orderdate, 'yyyy') as "Year",
count(distinct oh.customerkey) as "#Customers"
from orderheader oh
inner join country c on c.countrykey = oh.countrykey
group by c.countryname,
rollup(to_char(oh.orderdate, 'yyyy'))
order by 1 nulls first, 2 nulls first;

--4
select
to_char(oh.orderdate, 'yyyy') as "Year",
och.channelname as "Channel",
c.countryname as "Country",
sum(od.quantity * od.transactionprice) as "Total"
from orderheader oh
inner join country c on c.countrykey = oh.countrykey
inner join orderchannel och on och.channelkey = oh.channelkey
inner join orderdetail od on od.orderkey = oh.orderkey
group by cube(
    to_char(oh.orderdate, 'yyyy'),
    och.channelname,
    c.countryname
)
order by 1 nulls last, 2 nulls last, 3 nulls last;

--5
