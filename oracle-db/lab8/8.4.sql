--1
select
sum(od.quantity * od.transactionprice) as "Total orders value"
from orderdetail od;

--2
select
to_char(oh.orderdate, 'yyyy') Year,
sum(od.quantity * od.transactionprice) as "Total value"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
group by to_char(oh.orderdate, 'yyyy')
order by 1;

--3
select
pc.productcategoryname as "Product category",
to_char(oh.orderdate, 'yyyy') Year,
to_char(oh.orderdate, 'Month') Month,
sum(od.quantity * od.transactionprice) as "Total value"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
inner join productcategory pc on pc.productcategorykey = psc.productcategorykey
group by cube(
    pc.productcategoryname,
    to_char(oh.orderdate, 'yyyy'),
    to_char(oh.orderdate, 'Month')
)
order by 1, 2,
to_date(to_char(oh.orderdate, 'Month'), 'Month');

--4
select
to_char(oh.orderdate, 'yyyy') Year,
coalesce(c.countryname, 'All countries') as "Country",
sum(od.quantity * od.transactionprice) as "Total value"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join country c on c.countrykey = oh.countrykey
group by
to_char(oh.orderdate, 'yyyy'),
rollup(c.countryname)
order by 1 desc, 3 desc;

--5
select
pc.productcategoryname as "Product category",
to_char(oh.orderdate, 'Month') Month,
sum(od.quantity * od.transactionprice) as "Total value"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
inner join productcategory pc on pc.productcategorykey = psc.productcategorykey
inner join orderchannel och on och.channelkey = oh.channelkey
where
to_char(oh.orderdate, 'yyyy') = '2019'
and och.channelname = 'Mobile application'
group by
pc.productcategoryname,
to_char(oh.orderdate, 'Month')
order by 3;

--6
select
st.salesterritoryname as "Region",
coalesce(c.countryname, 'All countries') as "Country",
sum(od.quantity * od.transactionprice) as "Total value"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join country c on c.countrykey = oh.countrykey
inner join salesterritory st on st.salesterritorykey = c.salesterritorykey
group by
st.salesterritoryname,
rollup(c.countryname)
order by 1, 3 desc;

--7
select
c.countryname,
och.channelname,
coalesce(sum(od.quantity * od.transactionprice), 0) as "Total value"
from orderchannel och
left join (
    orderheader oh
    inner join country c on c.countrykey = oh.countrykey
    inner join orderdetail od on od.orderkey = oh.orderkey
) on och.channelkey = oh.channelkey
group by
c.countryname,
och.channelname
order by 1, 3 desc;

--8
select
to_char(oh.orderdate, 'yyyy') Year,
p.productname Product,
sum(od.quantity) as "#Items"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
group by
to_char(oh.orderdate, 'yyyy'),
p.productname
order by 1 desc, 3 desc;

--9
select
to_char(oh.orderdate, 'yyyy') Year,
c.countryname Country,
och.channelname Channel,
p.productname Product,
sum(od.quantity) as "#Items"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join orderchannel och on och.channelkey = oh.channelkey
inner join country c on c.countrykey = oh.countrykey
group by
to_char(oh.orderdate, 'yyyy'),
c.countryname,
och.channelname,
p.productname
order by 1, 2, 3, 5;
