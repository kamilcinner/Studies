--1
select
c.countryname Country,
to_char(oh.orderdate, 'yyyy') Year,
min(to_char(oh.orderdate, 'dd-mm-yyyy')) as "First Order Date"
from orderheader oh
inner join country c on c.countrykey = oh.countrykey
group by
c.countryname,
to_char(oh.orderdate, 'yyyy')
order by 1, 2 desc;

--2
select
c.customerkey as "Customer ID",
c.lastname || ' ' || c.firstname as "Customer Name",
'Q' || to_char(oh.orderdate, 'q') as "Quarter",
max(to_char(oh.orderdate, 'dd-mm-yyyy')) as "Last Purchase Date"
from orderheader oh
inner join customer c on c.customerkey = oh.customerkey
group by
c.customerkey,
c.lastname || c.firstname,
'Q' || to_char(oh.orderdate, 'q')
order by 1, 3;

--3
select
to_char(oh.orderdate, 'yyyy') Year,
max(od.discountamount) as "Max Discount Amount"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
where psc.productcategorykey = '1'
group by to_char(oh.orderdate, 'yyyy')
order by 1;

--4
select
c.customerkey as "Customer ID",
c.lastname || ' ' || c.firstname as "Customer Name",
max(od.transactionprice) as "Max Value"
from orderheader oh
inner join customer c on c.customerkey = oh.customerkey
inner join orderdetail od on od.orderkey = oh.orderkey
where c.lastname = 'Alan'
group by
c.customerkey,
c.lastname || c.firstname
order by 1;

--5
select
to_char(oh.orderdate, 'yyyy') Year,
c.countryname Country,
max(od.transactionprice) as "Max Trans Price"
from orderheader oh
inner join country c on c.countrykey = oh.countrykey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
where psc.productcategorykey = '1'
group by cube (
    to_char(oh.orderdate, 'yyyy'),
    c.countryname
)
order by 1 nulls first, 2 nulls first;
