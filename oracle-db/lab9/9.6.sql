--1
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

-- accept changes
commit;

--2
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

-- accept changes
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

-- accept changes
commit;

--4
