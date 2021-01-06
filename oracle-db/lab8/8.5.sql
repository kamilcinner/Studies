--1
select
to_char(oh.orderdate, 'yyyy') Year,
c.countryname Country,
round(avg(oh.deliverydate - oh.orderdate)) as "#Avg days"
from orderheader oh
inner join country c on c.countrykey = oh.countrykey
where oh.orderstatuskey = '4'
group by
to_char(oh.orderdate, 'yyyy'),
c.countryname
order by 1, 2;

--2
select
p.productname Product,
to_char(oh.orderdate, 'yyyy') Year,
'Q' || to_char(oh.orderdate, 'q') Quarter,
round(avg(od.transactionprice), 2) as "Avg Trans Price"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
group by
p.productname,
to_char(oh.orderdate, 'yyyy'),
'Q' || to_char(oh.orderdate, 'q')
order by 1, 2, 3;

--3
select
psc.productSubcategoryName Product,
to_char(oh.orderdate, 'yyyy') Year,
round(avg(od.discountamount), 2) as "Avg Discount"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
where psc.productcategorykey = '1'
group by
psc.productSubcategoryName,
to_char(oh.orderdate, 'yyyy')
order by 1, 2;

--4
select
psc.productSubcategoryName Product,
to_char(oh.orderdate, 'yyyy') Year,
round(avg(od.transactionprice), 2) as "Avg Trans Price"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
where psc.productSubcategoryName like '%Frames%'
group by
psc.productSubcategoryName,
to_char(oh.orderdate, 'yyyy')
order by 1, 2;

--5
select
psc.productSubcategoryName Product,
to_char(oh.orderdate, 'yyyy') Year,
'Q' || to_char(oh.orderdate, 'q') Quarter,
round(avg(od.transactionprice), 2) as "Avg Trans Price"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
where psc.productcategorykey = '1'
group by
psc.productSubcategoryName,
rollup(
    to_char(oh.orderdate, 'yyyy'),
    'Q' || to_char(oh.orderdate, 'q')
)
order by 1, 2 nulls first, 3 nulls first, 4 desc;
