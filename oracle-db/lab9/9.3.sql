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
