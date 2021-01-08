--1
select
extract(year from oh.orderdate) Year,
c.customerkey as "Customer ID",
c.lastname || ' ' || c.firstname as "Customer Name",
count(*) as "#Orders"
from orderheader oh
inner join customer c on c.customerkey = oh.customerkey
where oh.orderstatuskey != '5'
group by
extract(year from oh.orderdate),
c.customerkey,
c.lastname || ' ' || c.firstname
having count(*) = (
    select max(order_num) from (
        select
        count(*) order_num,
        extract(year from orderdate) year
        from orderheader
        where orderstatuskey != '5'
        group by
        customerkey,
        extract(year from orderdate)
    ) t
    where t.year = extract(year from oh.orderdate)
)
order by 1, 2;

--2
select
extract(year from oh.orderdate) Year,
p.productname Product,
sum(od.quantity) as "#Items"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join country c on c.countrykey = oh.countrykey
where c.countryname = 'Australia'
group by
extract(year from oh.orderdate),
p.productname,
p.productkey
having sum(od.quantity) = (
    select max(product_items) from (
        select
        sum(tod.quantity) product_items,
        extract(year from toh.orderdate) year
        from orderheader toh
        inner join orderdetail tod on tod.orderkey = toh.orderkey
        inner join country tc on tc.countrykey = toh.countrykey
        where tc.countryname = 'Australia'
        group by
        tod.productkey,
        extract(year from toh.orderdate)
    ) t
    where t.year = extract(year from oh.orderdate)
);

--3
select
extract(year from oh.orderdate) Year,
pc.productcategoryname Category,
p.productname Product,
count(distinct oh.customerkey) as "#Customers"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
inner join productcategory pc on pc.productcategorykey = psc.productcategorykey
group by
extract(year from oh.orderdate),
pc.productcategoryname,
pc.productcategorykey,
p.productname,
p.productkey
having count(distinct oh.customerkey) = (
    select max(t.customer_num) from (
        select
        count(distinct toh.customerkey) customer_num,
        extract(year from toh.orderdate) year,
        tpsc.productcategorykey category
        from orderheader toh
        inner join orderdetail tod on tod.orderkey = toh.orderkey
        inner join product tp on tp.productkey = tod.productkey
        inner join productsubcategory tpsc on tpsc.productsubcategorykey = tp.productsubcategorykey
        group by
        tp.productkey,
        extract(year from toh.orderdate),
        tpsc.productcategorykey
    ) t
    where t.year = extract(year from oh.orderdate)
    and t.category = pc.productcategorykey
);

--4


--10
select
extract(year from oh.orderdate) Year,
dm.deliverymethodname as "Delivery type",
count(*) as "#Orders"
from orderheader oh
inner join deliverymethod dm on oh.deliverymethodkey = dm.deliverymethodkey
group by
extract(year from oh.orderdate),
dm.deliverymethodname
having count(*) = (
    select max(order_num) from (
        select
        count(*) order_num,
        extract(year from orderdate) Year
        from orderheader
        group by
        deliverymethodkey,
        extract(year from orderdate)
    )
    where Year = extract(year from oh.orderdate)
);
