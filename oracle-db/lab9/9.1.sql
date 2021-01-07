--1
select oh.orderkey as "Order ID"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
group by oh.orderkey
having sum(od.transactionprice * od.quantity) = (
    select max(total_value) from (
        select sum(transactionprice * quantity) total_value
        from orderdetail
        group by orderkey
    )
);

--2
select
c.customerkey as "Customer ID",
c.lastname || ' ' || c.firstname as "Customer name",
max(oh.orderdate) as "Order Date"
from orderheader oh
inner join customer c on oh.customerkey = c.customerkey
group by
c.customerkey,
c.lastname || ' ' || c.firstname
having max(oh.orderdate) = (
    select max(orderdate) from orderheader
)
order by 2;

--3
select
c.customerkey as "Customer ID",
c.lastname || ' ' || c.firstname as "Customer name",
count(*) as "#Orders"
from orderheader oh
inner join customer c on oh.customerkey = c.customerkey
group by
c.customerkey,
c.lastname || ' ' || c.firstname
having count(*) = (
    select max(order_num) from (
        select distinct count(*) order_num
        from orderheader
        group by customerkey
    )
)
order by 2;

--4
select
p.productname Product,
count(distinct oh.orderkey) as "#Orders"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
where to_char(oh.orderdate, 'yyyy') = '2019'
group by p.productname
having count(distinct oh.orderkey) = (
    select max(order_num) from (
        select distinct count(distinct oh.orderkey) order_num
        from orderheader oh
        inner join orderdetail od on od.orderkey = oh.orderkey
        inner join product p on p.productkey = od.productkey
        where to_char(oh.orderdate, 'yyyy') = '2019'
        group by p.productname
    )
);

--5
select
p.productname Product,
count(distinct oh.customerkey) as "#Customers"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
group by p.productname
having count(distinct oh.customerkey) = (
    select max(customer_num) from (
        select distinct count(distinct oh.customerkey) customer_num
        from orderheader oh
        inner join orderdetail od on od.orderkey = oh.orderkey
        inner join product p on p.productkey = od.productkey
        group by p.productname
    )
);

--6
select
c.countryname Country,
count(distinct oh.orderkey) as "#Orders"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
inner join country c on c.countrykey = oh.countrykey
where psc.productcategorykey = '1'
group by c.countryname
having count(distinct oh.orderkey) = (
    select max(order_num) from (
        select distinct count(distinct od.orderkey) order_num
        from orderheader oh
        inner join orderdetail od on od.orderkey = oh.orderkey
        inner join product p on p.productkey = od.productkey
        inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
        inner join country c on c.countrykey = oh.countrykey
        where psc.productcategorykey = '1'
        group by c.countryname
    )
);

--7
select
och.channelname Channel,
count(distinct oh.customerkey) as "#Customers"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
inner join orderchannel och on och.channelkey = oh.channelkey
where psc.productcategorykey = '4'
group by och.channelname
having count(distinct oh.customerkey) = (
    select max(customer_num) from (
        select count(distinct oh.customerkey) customer_num
        from orderheader oh
        inner join orderdetail od on od.orderkey = oh.orderkey
        inner join product p on p.productkey = od.productkey
        inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
        inner join orderchannel och on och.channelkey = oh.channelkey
        where psc.productcategorykey = '4'
        group by och.channelname
    )
);

--8
select
to_char(oh.orderdate, 'Month') Month,
count(distinct oh.customerkey) as "#Customers"
from orderheader oh
where to_char(oh.orderdate, 'yyyy') = '2019'
group by to_char(oh.orderdate, 'Month')
having count(distinct oh.customerkey) = (
    select max(customer_num) from (
        select count(distinct oh.customerkey) customer_num
        from orderheader oh
        where to_char(oh.orderdate, 'yyyy') = '2019'
        group by to_char(oh.orderdate, 'Month')
    )
);

--9
select
c.countryname Country,
count(*) as "#Canceled orders"
from orderheader oh
inner join country c on c.countrykey = oh.countrykey
inner join orderstatus os on os.orderstatuskey = oh.orderstatuskey
where os.orderstatusname = 'Canceled'
group by c.countryname
having count(*) = (
    select max(order_num) from (
        select distinct count(*) order_num
        from orderheader oh
        inner join country c on c.countrykey = oh.countrykey
        inner join orderstatus os on os.orderstatuskey = oh.orderstatuskey
        where os.orderstatusname = 'Canceled'
        group by c.countryname
    )
);

--10
select
oh.orderkey "Order number",
sum(od.transactionprice * od.quantity) as "Order value"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join country c on c.countrykey = oh.countrykey
where c.countryname = 'Australia'
group by oh.orderkey
having sum(od.transactionprice * od.quantity) > (
    select avg(order_value) from (
        select sum(od.transactionprice * od.quantity) order_value
        from orderheader oh
        inner join orderdetail od on od.orderkey = oh.orderkey
        inner join country c on c.countrykey = oh.countrykey
        where c.countryname = 'Australia'
        group by oh.orderkey
    )
)
order by 2 desc;
