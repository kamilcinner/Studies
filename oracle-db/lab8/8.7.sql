--1
select
to_char(oh.orderdate, 'yyyy') Year,
psc.productSubcategoryName Product,
count(distinct oh.customerkey) as "#Customers",
sum(od.transactionprice * od.quantity) as "Total value"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
where psc.productcategorykey = '1'
group by
to_char(oh.orderdate, 'yyyy'),
psc.productSubcategoryName
order by 1, 2;

--2
select
to_char(oh.orderdate, 'yyyy') Year,
c.countryname Country,
pc.productcategoryname Product,
count(distinct oh.orderkey) as "#Orders",
sum(od.transactionprice * od.quantity) as "Total value"
from orderheader oh
inner join country c on c.countrykey = oh.countrykey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
inner join productCategory pc on pc.productCategoryKey = psc.productCategoryKey
group by
to_char(oh.orderdate, 'yyyy'),
c.countryname,
pc.productcategoryName
order by 1 desc, 2, 5 desc;

--3
select
to_char(oh.orderdate, 'yyyy') Year,
c.customerkey as "Customer ID",
c.lastname || ' ' || c.firstname as "Customer Name",
count(distinct oh.orderkey) as "#Orders",
sum(od.transactionprice * od.quantity) as "Total value"
from orderheader oh
inner join customer c on c.customerkey = oh.customerkey
inner join orderdetail od on od.orderkey = oh.orderkey
group by
to_char(oh.orderdate, 'yyyy'),
c.customerkey,
c.lastname || ' ' || c.firstname
order by 1 desc, 5 desc;

--4
select
to_char(oh.orderdate, 'yyyy') Year,
c.countryname Country,
count(distinct oh.customerkey) as "#Customers",
sum(od.transactionprice * od.quantity) as "Total value",
round(
    sum(od.transactionprice * od.quantity) / count(distinct oh.orderkey), 2
) as "Avg Customer Value"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join country c on c.countrykey = oh.countrykey
group by
to_char(oh.orderdate, 'yyyy'),
c.countryname
order by 1, 4;

--5
select
to_char(oh.orderdate, 'yyyy') Year,
to_char(oh.orderdate, 'Month') Month,
st.salesterritoryname Region,
count(distinct oh.customerkey) as "#Customers",
sum(od.transactionprice * od.quantity) as "Total value"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join country c on c.countrykey = oh.countrykey
inner join salesterritory st on st.salesterritorykey = c.salesterritorykey
group by
to_char(oh.orderdate, 'yyyy'),
rollup(
    to_char(oh.orderdate, 'Month'),
    st.salesterritoryname
)
order by 1, 2 nulls first, 3 nulls first;

--6
select
to_char(oh.orderdate, 'yyyy') Year,
och.channelname Channel,
c.countryname Country,
count(distinct oh.orderkey) as "#Orders",
sum(od.transactionprice * od.quantity) as "Total value",
round(
    sum(od.transactionprice * od.quantity) / count(distinct oh.orderkey), 2
) as "Avg Order Value"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join country c on c.countrykey = oh.countrykey
inner join orderchannel och on och.channelkey = oh.channelkey
group by
to_char(oh.orderdate, 'yyyy'),
och.channelname,
c.countryname
order by 1, 6;
