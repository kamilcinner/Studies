--1
select count(oh.orderkey) as "#Orders"
from orderheader oh
where to_char(oh.orderdate, 'yyyy') = '2019';

--2
select
c.customerkey,
c.lastname,
c.firstname,
count(oh.orderkey) as "#Orders"
from orderheader oh
inner join customer c on c.customerkey = oh.customerkey
where to_char(oh.orderdate, 'yyyy') = '2019'
group by
c.customerkey,
c.lastname,
c.firstname
order by 4 desc;

--3
select
oh.orderkey,
count(distinct od.productkey) as "#Products"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
where to_char(oh.orderdate, 'q yyyy') = '1 2018'
group by oh.orderkey
order by 2 desc;

--4
select
to_char(oh.orderdate, 'yyyy') Year,
to_char(oh.orderdate, 'mm') as "Month number",
count(*) as "#Orders"
from orderheader oh
group by
to_char(oh.orderdate, 'yyyy'),
to_char(oh.orderdate, 'mm')
order by 1, 2;

--5
select
to_char(oh.orderdate, 'yyyy') Year,
to_char(oh.orderdate, 'mm') as "Month number",
count(*) as "#Orders"
from orderheader oh
group by
to_char(oh.orderdate, 'yyyy'),
rollup(to_char(oh.orderdate, 'mm'))
order by 1, 2 nulls first;

--6
select
st.salesterritoryname as "Region",
to_char(oh.orderdate, 'yyyy') Year,
to_char(oh.orderdate, 'Month') Month,
count(oh.orderkey) as "#Orders"
from orderheader oh
inner join country c on c.countrykey = oh.countrykey
inner join salesterritory st on st.salesterritorykey = c.salesterritorykey
group by
st.salesterritoryname,
to_char(oh.orderdate, 'yyyy'),
to_char(oh.orderdate, 'Month')
order by 1, 2, 3;

--7
select
st.salesterritoryname as "Region",
c.countryname as "Country",
count(oh.orderkey) as "#Orders"
from orderheader oh
inner join country c on c.countrykey = oh.countrykey
inner join salesterritory st on st.salesterritorykey = c.salesterritorykey
group by
st.salesterritoryname,
rollup(c.countryname)
order by 1, 2 nulls first;

--8
select
to_char(oh.orderdate, 'yyyy') as "Year",
pc.productcategoryname as "Product category",
count(distinct oh.orderkey) as "#Orders"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
inner join productcategory pc on pc.productcategorykey = psc.productcategorykey
group by
to_char(oh.orderdate, 'yyyy'),
pc.productcategoryname
order by 1, 2;

--9
select
pc.productcategoryname as "Product category",
psc.productSubcategoryName as "Product subcategory",
count(distinct oh.orderkey) as "#Orders"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
inner join productcategory pc on pc.productcategorykey = psc.productcategorykey
group by
pc.productcategoryname,
rollup(psc.productSubcategoryName)
order by 1, 2 nulls first;

--10
select
c.countryname as "Country",
och.channelname as "Channel",
count(oh.orderkey) as "#Orders"
from orderheader oh
inner join orderchannel och on och.channelkey = oh.channelkey
inner join country c on c.countrykey = oh.countrykey
group by
c.countryname,
och.channelname
order by 1;

--11
select
c.customerkey,
c.lastname,
c.firstname,
count(oh.orderkey) as "#Canceled"
from orderheader oh
inner join customer c on c.customerkey = oh.customerkey
where oh.orderstatuskey = '5'
group by
c.customerkey,
c.lastname,
c.firstname
order by 4 desc;

--12
select
to_char(oh.orderdate, 'yyyy') as "Year",
c.countryname as "Country name",
count(distinct oh.customerkey) as "#Customers"
from orderheader oh
inner join country c on c.countrykey = oh.countrykey
group by
to_char(oh.orderdate, 'yyyy'),
c.countryname
order by 1, 2;

--13
select
c.customerkey,
c.lastname,
c.fristname,
count(distinct od.productkey) as "#Products"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join customer c on c.customerkey = oh.customerkey
group by
c.customerkey,
c.lastname,
c.fristname
order by 4 desc;

--14
select
to_char(oh.orderdate, 'yyyy') as "Year",
coalesce(st.salesterritoryname, 'All regions') as "Region",
coalesce(c.countryname, 'All countries') as "Country",
count(distinct oh.customerkey) as "#Customers"
from orderheader oh
inner join country c on c.countrykey = oh.countrykey
inner join salesterritory st on st.salesterritorykey = c.salesterritorykey
group by
to_char(oh.orderdate, 'yyyy'),
rollup(
    st.salesterritoryname,
    c.countryname
)
order by 1, 2, 4;
