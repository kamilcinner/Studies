--1
select
st.salesterritoryname as "Region",
to_char(oh.orderdate, 'yyyy') as "Year",
sum(od.quantity * od.transactionprice)
from salesterritory st
inner join country c on c.salesterritorykey = st.salesterritorykey
inner join orderheader oh on oh.countrykey = c.countrykey
inner join orderdetail od on od.orderkey = oh.orderkey
group by st.salesterritoryname, to_char(oh.orderdate, 'yyyy')
order by 2 desc, 1 asc;

--2
select
to_char(oh.orderdate, 'yyyy') Year,
coalesce(to_char(oh.orderdate, 'Month'), 'Year total') Month,
sum(od.quantity * od.transactionprice) Total
from orderheader oh
inner join orderdetail od on oh.orderkey = od.orderkey
group by to_char(oh.orderdate, 'yyyy'),
rollup(to_char(oh.orderdate, 'Month'))
order by 1,
to_date(to_char(oh.orderdate, 'Month'), 'Month') nulls first;

--3 cube???
select
to_char(oh.orderdate, 'yyyy') Year,
to_char(oh.orderdate, 'Month') Month,
sum(od.quantity * od.transactionprice) Total
from orderheader oh
inner join orderdetail od on oh.orderkey = od.orderkey
cube(to_char(oh.orderdate, 'Month'), to_char(oh.orderdate, 'yyyy'))
order by 1,
to_date(to_char(oh.orderdate, 'Month'), 'Month') nulls first;

--4
select
to_char(oh.orderdate, 'yyyy') Year,
to_char(oh.orderdate, 'Month') Month,
count(*) as "#Orders"
from orderheader oh
group by
to_char(oh.orderdate, 'yyyy'),
to_char(oh.orderdate, 'Month')
order by 1,
to_date(to_char(oh.orderdate, 'Month'), 'Month');

--4.1
select
to_char(oh.orderdate, 'yyyy') Year,
to_char(oh.orderdate, 'Month') Month,
count(distinct oh.customerkey) as "#Customer"
from orderheader oh
group by
to_char(oh.orderdate, 'yyyy'),
to_char(oh.orderdate, 'Month')
order by 1,
to_date(to_char(oh.orderdate, 'Month'), 'Month');

--5
select
co.countryname Country,
count(distinct oh.customerkey) as "#Customers"
from country co
inner join orderheader oh on oh.countrykey = co.countrykey
where to_char(oh.orderdate, 'yyyy') = '2019'
group by co.countryname
having count(distinct oh.customerkey) > 1500
order by 2 desc;