--1 same as 9.1.1 (maybe this should be a different solution)
select
oh.orderkey as "Order ID",
oh.customerkey Customer,
oh.countrykey Country
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
group by
oh.orderkey,
oh.customerkey,
oh.countrykey
having sum(od.transactionprice * od.quantity) = (
    select max(order_value) from (
        select sum(transactionprice * quantity) order_value
        from orderdetail
        group by orderkey
    )
);

--2
select
customerkey as "Customer ID",
lastname || ' ' || firstname as "Customer Name"
from customer
where customerkey in (
    select distinct oh.customerkey
    from orderheader oh
    where to_char(oh.orderdate, 'mm-yyyy') = '12-2019'
)
and customerkey not in (
    select distinct oh.customerkey
    from orderheader oh
    where to_char(oh.orderdate, 'mm-yyyy') = '01-2020'
)
order by 2;

--3
select distinct productname Product
from product
where productkey in (
    select distinct od.productkey
    from orderheader oh
    inner join orderdetail od on od.orderkey = oh.orderkey
    inner join country c on c.countrykey = oh.countrykey
    inner join salesterritory st on st.salesterritorykey = c.salesterritorykey
    where st.salesterritoryname = 'North America'
)
and productkey in (
    select distinct od.productkey
    from orderheader oh
    inner join orderdetail od on od.orderkey = oh.orderkey
    inner join country c on c.countrykey = oh.countrykey
    inner join salesterritory st on st.salesterritorykey = c.salesterritorykey
    where st.salesterritoryname = 'Australia'
);

--4 this solution gives 1807 records but is kinda sketchy
select distinct
c.customerkey as "Customer ID",
c.lastname || ' ' || c.firstname as "Customer Name",
co.countryname Country,
coc.countryname ClientHomeCountry
from orderheader oh
inner join customer c on c.customerkey = oh.customerkey
inner join city ci on ci.citykey = c.citykey
inner join country coc on coc.countrykey = ci.countrykey
inner join country co on co.countrykey = oh.countrykey
where to_char(oh.orderdate, 'mm-yyyy') = '06-2020'
and ci.countrykey != oh.countrykey
order by 2, 3;

--5
select
tab.year "Year",
max(tab.order_number) as "#Max Monthy Orders"
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

--6
select
extract(year from order_date) Year,
round(avg(order_value), 2) as "Avg Order Value"
from (
    select
    oh.orderkey,
    oh.orderdate order_date,
    sum(od.transactionprice * od.quantity) order_value
    from orderheader oh
    inner join orderdetail od on od.orderkey = oh.orderkey
    group by
    oh.orderkey,
    oh.orderdate
)
group by extract(year from order_date);

--7
select
extract(year from oh.orderdate) Year,
to_char(oh.orderdate, 'Month') Month,
c.countryname Country,
round(avg(t.order_value), 2) as "Avg Order Value"
from orderheader oh
inner join country c on c.countrykey = oh.countrykey
inner join (
    select
    od.orderkey orderkey,
    sum(od.transactionprice * od.quantity) order_value
    from orderdetail od
    group by od.orderkey
) t on t.orderkey = oh.orderkey
group by
extract(year from oh.orderdate),
to_char(oh.orderdate, 'Month'),
c.countryname
order by
1,
to_date(to_char(oh.orderdate, 'Month'), 'Month'),
4 desc;

--8
select
extract(year from oh.orderdate) Year,
och.channelname Channel,
max(order_value) as "Max Order Value",
round(avg(t.order_value), 2) as "Avg Order Value"
from orderchannel och
left join (
    orderheader oh
    inner join (
        select
        od.orderkey orderkey,
        sum(od.transactionprice * od.quantity) order_value
        from orderdetail od
        group by od.orderkey
    ) t on t.orderkey = oh.orderkey
) on och.channelkey = oh.channelkey
group by
extract(year from oh.orderdate),
och.channelname
order by 1, 2;

--9
select distinct
c.customerkey as "Customer ID",
c.lastname as "Last Name",
c.firstname as "First Name"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join customer c on c.customerkey = oh.customerkey
inner join country co on co.countrykey = oh.countrykey
where co.countryname = 'Australia'
group by
c.customerkey,
c.lastname,
c.firstname,
oh.orderkey
having sum(od.transactionprice * od.quantity) > (
    select avg(order_value) from (
        select sum(od.transactionprice * od.quantity) order_value
        from orderdetail od
        inner join orderheader oh on oh.orderkey = od.orderkey
        inner join country c on c.countrykey = oh.countrykey
        where c.countryname = 'Australia'
        group by od.orderkey
    )
)
order by 2;
