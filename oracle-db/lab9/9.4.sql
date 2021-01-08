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
select
extract(year from oh.orderdate) Year,
c.customerkey as "Customer ID",
c.lastname || ' ' || c.firstname as "Customer Name",
sum(od.transactionprice * od.quantity) as "Max Order Value"
from orderheader oh
inner join customer c on c.customerkey = oh.customerkey
inner join orderdetail od on od.orderkey = oh.orderkey
group by
extract(year from oh.orderdate),
c.customerkey,
c.lastname || ' ' || c.firstname,
oh.orderkey
having sum(od.transactionprice * od.quantity) = (
    select t2.max_order_value from (
        select
        max(order_value) max_order_value,
        extract(year from t1.orderdate) year
        from (
            select
            sum(tod.transactionprice * tod.quantity) order_value,
            toh.orderdate
            from orderdetail tod
            inner join orderheader toh on toh.orderkey = tod.orderkey
            group by
            toh.orderkey,
            toh.orderdate
        ) t1
        group by extract(year from t1.orderdate)
    ) t2
    where t2.year = extract(year from oh.orderdate)
);

--5
select
extract(year from oh.orderdate) Year,
to_char(oh.orderdate, 'Month') Month,
sum(od.transactionprice * od.quantity) as "Max Total Value"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
where oh.orderstatuskey = '4'
group by
extract(year from oh.orderdate),
to_char(oh.orderdate, 'Month')
having sum(od.transactionprice * od.quantity) = (
    select max(t.month_value) from (
        select
        sum(tod.transactionprice * tod.quantity) month_value,
        extract(year from toh.orderdate) year
        from orderheader toh
        inner join orderdetail tod on tod.orderkey = toh.orderkey
        where toh.orderstatuskey = '4'
        group by
        extract(year from toh.orderdate),
        extract(month from toh.orderdate)
    ) t
    where t.year = extract(year from oh.orderdate)
);

--6
select
extract(year from oh.orderdate) Year,
och.channelname Channel,
c.customerkey as "Customer ID",
c.lastname || ' ' || c.firstname as "Customer Name",
sum(od.transactionprice * od.quantity) as "Max Order Value"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join orderchannel och on och.channelkey = oh.channelkey
inner join customer c on c.customerkey = oh.customerkey
group by
extract(year from oh.orderdate),
och.channelname,
c.customerkey,
c.lastname || ' ' || c.firstname,
oh.orderkey
having sum(od.transactionprice * od.quantity) = (
    select max(t.order_value) from (
        select
        sum(tod.transactionprice * tod.quantity) order_value,
        extract(year from toh.orderdate) year,
        toch.channelname channel
        from orderheader toh
        inner join orderdetail tod on tod.orderkey = toh.orderkey
        inner join orderchannel toch on toch.channelkey = toh.channelkey
        group by
        toh.orderkey,
        extract(year from toh.orderdate),
        toch.channelname
    ) t
    where t.year = extract(year from oh.orderdate)
    and t.channel = och.channelname
)
order by 1, 2;

--7
select
c.countryname Country,
'Y' || extract(year from oh.orderdate) Year,
p.productname Product,
sum(od.quantity) as "#Items"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join country c on c.countrykey = oh.countrykey
group by
c.countryname,
'Y' || extract(year from oh.orderdate),
p.productname
having sum(od.quantity) = (
    select max(t.product_items) from (
        select
        sum(tod.quantity) product_items,
        tc.countryname country,
        extract(year from toh.orderdate) year
        from orderheader toh
        inner join orderdetail tod on tod.orderkey = toh.orderkey
        inner join country tc on tc.countrykey = toh.countrykey
        group by
        tod.productkey,
        tc.countryname,
        extract(year from toh.orderdate)
    ) t
    where 'Y' || t.year = 'Y' || extract(year from oh.orderdate)
    and t.country = c.countryname
)
order by 1, 2;

--8
select
'Y' || extract(year from oh.orderdate) Year,
'Q' || to_char(oh.orderdate, 'q') Quarter,
psc.productsubcategoryname Product,
sum(od.quantity) as "#Items"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
group by
'Y' || extract(year from oh.orderdate),
'Q' || to_char(oh.orderdate, 'q'),
psc.productsubcategoryname
having sum(od.quantity) = (
    select max(t.product_items) from (
        select
        sum(tod.quantity) product_items,
        extract(year from toh.orderdate) year,
        to_char(toh.orderdate, 'q') quarter
        from orderheader toh
        inner join orderdetail tod on tod.orderkey = toh.orderkey
        inner join product tp on tp.productkey = tod.productkey
        group by
        tp.productsubcategorykey,
        extract(year from toh.orderdate),
        to_char(toh.orderdate, 'q')
    ) t
    where 'Y' || t.year = 'Y' || extract(year from oh.orderdate)
    and 'Q' || t.quarter = 'Q' || to_char(oh.orderdate, 'q')
)
order by 1, 2;

--9


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
