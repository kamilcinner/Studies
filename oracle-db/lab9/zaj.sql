--1
select
c.customerkey,
c.firstname,
c.lastname
from orderheader oh inner join customer c
on oh.customerkey = c.customerkey
group by c.customerkey, c.firstname, c.lastname
having count(*) =
(
    select
    max(order_num)
    from
    (
        select distinct
        count(*) order_num
        from orderheader
        group by customerkey
    )
);

--2
select
c.customerkey,
c.lastname,
c.firstname
from customer c inner join orderheader oh
on oh.customerkey = c.customerkey
where (oh.countrykey, oh.orderdate) =
(
    select
    c.countrykey,
    max(orderdate)
    from orderheader oh inner join country c
    on c.countrykey = oh.countrykey
    where c.countryname = 'Australia'
    group by c.countrykey
);

--3
select
customerkey,
firstname,
lastname
from customer
where customerkey in
(
    select
    oh.customerkey
    from orderheader oh
    where to_char(oh.orderdate, 'mm-yyyy') = '12-2019'
)
and customerkey not in
(
    select
    oh.customerkey
    from orderheader oh
    where to_char(oh.orderdate, 'mm-yyyy') = '01-2020'
);

--4
select
tab.year "Year",
max(tab.order_number) as "#Orders"
from
(
    select
    extract(year from orderdate) year,
    extract(month from orderdate) month,
    count(*) order_number
    from orderheader oh
    group by
    extract(year from orderdate),
    extract(month from orderdate)
) tab
group by tab.year;

--5
select
c.customerkey,
c.firstname,
c.lastname,
(
    select count(*) from customer
    where citykey = c.citykey and customerkey <> c.customerkey
) neighbours_num
from customer c;

--6
select
extract(year from oh.orderdate) Year,
dm.deliverymethodname as "Delivery type",
count(*) as "#Orders"
from orderheader oh inner join deliverymethod dm
on oh.deliverymethodkey = dm.deliverymethodkey
group by
extract(year from oh.orderdate),
dm.deliverymethodname
having count(*) =
(
    select max(order_num) from
    (
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

--7
create table CustEUOrders(
    CustomerKey number(10),
    LastName varchar(45),
    FirstName varchar(45),
    OrderYear number(4),
    TotalOrderValue number(10,2),
    NumOrders number(5),
    AvgOrderValue number(10,2),
    MinOrderValue number(10,2),
    MaxOrderValue number(10,2)
);

insert all into CustEUOrders
select
customerkey, firstname, lastname, OrderYear, OrderMonth,
sum(OrderTotal), count(*), avg(OrderTotal), min(OrderTotal), max(OrderTotal)
from
(
    select
    c.customerkey,
    c.lastname,
    c.firstname,
    extract(year from oh.orderdate) OrderYear,
    extract(month from oh.orderdate) OrderMonth,
    sum(od.transactionprice * od.quantity) OrderTotal
    from customer c
    inner join orderheader oh on c.customerkey = oh.customerkey
    inner join orderdetail od on od.orderkey = oh.orderkey
    inner join country co on co.countrykey = oh.countrykey
    inner join salesterritory st on st.salesterritorykey = co.salesterritorykey
    where st.salesterritoryname = 'Europe'
    group by
    c.customerkey,
    c.lastname,
    c.firstname,
    extract(year from oh.orderdate),
    extract(month from oh.orderdate),
    oh.orderkey
)
group by
customerkey, firstname, lastname, OrderYear, OrderMonth;

--8
update orderheader
set deliverycost = 0
where orderkey in
(
    select
    oh.orderkey,
    from orderheader oh inner join orderdetail od
    on oh.orderkey = od.orderkey
    where extract(year from orderdate) = 2020
    having sum(transactionprice * quantity) > 7300
    group by oh.deliverycost
);

-- check
select
oh.orderkey,
oh.deliverycost
from orderheader oh inner join orderdetail od
on oh.orderkey = od.orderkey
where extract(year from orderdate) = 2020
having sum(transactionprice * quantity) > 7300
group by oh.orderkey, oh.deliverycost;

commit;

--9
create table CustomerBackup as select * from customer;

delete from CustomerBackup
where customerkey not in
(
    select distinct customerkey from orderheader
);

select * from customer
minus
select * from CustomerBackup;
