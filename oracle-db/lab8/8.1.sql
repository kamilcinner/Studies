--1
select
st.salesterritoryname as "Region",
to_char(oh.orderdate, 'yyyy') as "Year",
sum(od.quantity * od.transactionprice) as "Total"
from salesterritory st
inner join country c on c.salesterritorykey = st.salesterritorykey
inner join orderheader oh on oh.countrykey = c.countrykey
inner join orderdetail od on od.orderkey = oh.orderkey
group by st.salesterritoryname, to_char(oh.orderdate, 'yyyy')
order by 2 desc, 1 asc;

--2
select
to_char(oh.orderdate, 'yyyy') Year,
to_char(oh.orderdate, 'Month') Month,
count(oh.orderkey) as "#Orders"
from orderheader oh
group by
to_char(oh.orderdate, 'yyyy'),
to_char(oh.orderdate, 'Month')
order by 1, to_date(to_char(oh.orderdate, 'Month'), 'Month');

--3
select
pc.productcategoryname as "Product category",
oc.channelname as "Order channel",
count(distinct oh.customerkey) as "#Customers"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
inner join productcategory pc on pc.productcategorykey = psc.productcategorykey
inner join orderchannel oc on oc.channelkey = oh.channelkey
group by
pc.productcategoryname,
oc.channelname
order by 1, 2;

--4
select
st.salesterritoryname as "Region",
c.countryname as "Country"
to_char(oh.orderdate, 'yyyy') as "Year",
sum(od.quantity * od.transactionprice) as "Total"
from salesterritory st
inner join country c on c.salesterritorykey = st.salesterritorykey
inner join orderheader oh on oh.countrykey = c.countrykey
inner join orderdetail od on od.orderkey = oh.orderkey
group by
st.salesterritoryname,
c.countryname,
to_char(oh.orderdate, 'yyyy')
order by 1, 2, 3;

--5
select
to_char(oh.orderdate, 'yyyy') as "Year",
st.salesterritoryname as "Region",
pc.productcategoryname as "Product category",
count(oh.orderkey) as "#Orders"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
inner join productcategory pc on pc.productcategorykey = psc.productcategorykey
inner join country c on c.countrykey = oh.countrykey
inner join salesterritory st on st.salesterritorykey = c.salesterritorykey
group by
to_char(oh.orderdate, 'yyyy')
st.salesterritoryname,
pc.productcategoryname
order by 1, 2, 3;

--6
select
to_char(oh.orderdate, 'yyyy') as "Year",
'Q' || to_char(oh.orderdate, 'q') as "Quarter",
c.countryname as "Country",
och.channelname as "Channel",
p.productname as "Product",
sum(od.quantity) as "#Quantity total"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join country c on c.countrykey = oh.countrykey
inner join orderchannel och on och.channelkey = oh.channelkey
group by
to_char(oh.orderdate, 'yyyy'),
to_char(oh.orderdate, 'q'),
c.countryname,
och.channelname,
p.productname
order by 1, 2, 3, 4, 5;
