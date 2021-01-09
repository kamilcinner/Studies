--1
-- update
update orderheader set deliverycost = 0
where orderkey in (
    select
    oh.orderkey
    from orderheader oh
    inner join orderdetail od on oh.orderkey = od.orderkey
    where extract(year from orderdate) = 2020
    having sum(transactionprice * quantity) > 7300
    group by oh.orderkey
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

-- apply changes
commit;

--2
-- update
update orderheader set deliverydate = deliverydate + 1
where orderkey in (
    select
    orderkey
    from orderheader
    where to_char(deliverydate, 'day') like 'sunday%'
);

-- check
select
orderkey,
to_char(deliverydate, 'day')
from orderheader
where to_char(deliverydate, 'day') like 'sunday%';

-- apply changes
commit;

--3
-- check 1
select
oh.orderkey,
od.discountpctg,
od.discountamount,
od.transactionprice
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
where psc.productsubcategoryname = 'Mountain Bikes'
and to_char(oh.orderdate, 'mm-yyyy') = '06-2020'
and od.discountpctg < 10,
order by 1;

-- update
update orderdetail set
discountpctg = 15,
discountamount = (0.15 * (transactionprice + discountamount)),
transactionprice = (transactionprice + discountamount) - (0.15 * (transactionprice + discountamount))
where (orderkey, productkey) in (
    select
    oh.orderkey,
    od.productkey
    from orderheader oh
    inner join orderdetail od on od.orderkey = oh.orderkey
    inner join product p on p.productkey = od.productkey
    inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
    where psc.productsubcategoryname = 'Mountain Bikes'
    and to_char(oh.orderdate, 'mm-yyyy') = '06-2020'
    and od.discountpctg < 10
);

-- check 2
select
oh.orderkey,
od.discountpctg,
od.discountamount,
od.transactionprice
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
where psc.productsubcategoryname = 'Mountain Bikes'
and to_char(oh.orderdate, 'mm-yyyy') = '06-2020'
and od.discountpctg = 15
order by 1;

-- apply changes
commit;

--4
-- check
select
orderkey,
productkey,
transactionprice,
quantity
from orderdetail
where orderkey in (
    select od.orderkey
    from orderdetail od
    inner join orderheader oh on oh.orderkey = od.orderkey
    where extract(year from oh.orderdate) = '2020'
    group by od.orderkey
    having sum(od.transactionprice * od.quantity) > 7300
    and count(*) > 1
)
order by 1, 3 desc, 4 desc;

-- update
update orderdetail set quantity = quantity + 1
where (orderkey, productkey) in (
    select
    od.orderkey,
    od.productkey
    from orderdetail od
    where od.orderkey in (
        select od.orderkey
        from orderdetail od
        inner join orderheader oh on oh.orderkey = od.orderkey
        where extract(year from oh.orderdate) = '2020'
        group by od.orderkey
        having sum(od.transactionprice * od.quantity) > 7300
        and count(*) > 1
    )
    and od.transactionprice = (
        select min(tod.transactionprice)
        from orderdetail tod
        where tod.orderkey = od.orderkey
    )
);

-- apply changes
commit;

--5
-- update 1
alter table Customer
add Status number(1);

-- check 1
select * from Customer;

-- update 2
update Customer set status = case
when (
    customerkey in (
        select customerkey from orderheader
    )
) then 1
else 0
end;

-- check 2
select * from Customer where status = 0;
select * from Customer where status = 1;

-- apply changes
commit;

--6
-- update
update CustEUOrders eu set (MinOrderValue, MaxOrderValue) = (
    select min(t.OrderTotal), max(t.OrderTotal) from (
        select
        c.customerkey,
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
        extract(year from oh.orderdate),
        extract(month from oh.orderdate),
        oh.orderkey
    ) t
    where t.customerkey = eu.customerkey
    and t.OrderYear = eu.OrderYear
    and t.OrderMonth = eu.OrderMonth
);

-- check
select * from CustEUOrders;

--7
