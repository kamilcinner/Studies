--1
drop table CustEUOrders;

create table CustEUOrders(
    CustomerKey number(10),
    LastName varchar(45),
    FirstName varchar(45),
    OrderYear number(4),
    OrderMonth number(2),
    TotalOrderValue number(10,2),
    NumOrders number(5),
    AvgOrderValue number(10,2),
    MinOrderValue number(10,2),
    MaxOrderValue number(10,2)
);

insert into CustEUOrders (
    customerkey, lastname, firstname, orderyear, ordermonth,
    totalordervalue, numorders, avgordervalue
)
select
customerkey, lastname, firstname, OrderYear, OrderMonth,
sum(OrderTotal), count(*), avg(OrderTotal)
from (
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
group by customerkey, firstname, lastname, OrderYear, OrderMonth;

select * from CustEUOrders;

--2
drop table ProductOrders;

create table ProductOrders (
    ProductKey number(5),
    ProductName varchar2(40),
    OrderYear number(4),
    CountryName varchar2(50),
    TotalValue number(10,2),
    TotalItems number(6),
    AvgTransactionPrice number(10,2)
);

insert into ProductOrders (
    productkey, productname, orderyear, countryname,
    totalvalue, totalitems
)
select
p.productkey,
p.productname,
extract(year from oh.orderdate),
c.countryname,
sum(od.transactionprice * od.quantity),
sum(od.quantity)
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join country c on c.countrykey = oh.countrykey
group by
p.productkey,
p.productname,
extract(year from oh.orderdate),
c.countryname;

select * from ProductOrders;
