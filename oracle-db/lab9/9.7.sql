--1
-- copy
create table CustomerBackup as select * from customer;

-- delete
delete from CustomerBackup
where customerkey not in (
    select distinct customerkey from orderheader
);

-- check
select * from customer
minus
select * from CustomerBackup;

-- apply changes
commit;

--2
-- copy (610 records)
create table ProductBackup as select * from Product;

-- delete
delete from ProductBackup pb
where pb.productkey not in (
    select distinct od.productkey
    from orderdetail od
    inner join orderheader oh on od.orderkey = oh.orderkey
    group by
    od.productkey,
    extract(year from oh.orderdate)
    having sum(od.quantity) > 10
);

-- check (477 records)
select * from Product
minus
select * from ProductBackup;

-- apply changes
commit;

--3
-- delete
delete from ProductBackup pb
where pb.productkey in (
    select distinct od.productkey
    from orderdetail od
    inner join orderheader oh on od.orderkey = oh.orderkey
    where extract(year from oh.orderdate) = '2020'
    group by
    od.productkey
    having sum(od.quantity) < 10
);

-- check
select * from Product
minus
select * from ProductBackup;

-- apply changes
commit;

--4
-- copy
create table CountryBackup as select * from Country;

-- delete
delete from CountryBackup cb
where cb.countrykey in (
    select min() from (
        select
        oh.countrykey,
        count(*) orders_num
        from orderheader oh
        group by oh.countrykey
    )
)

--5
-- copy
create table DeliveryMethodBackup as select * from DeliveryMethod;

-- delete
delete from DeliveryMethodBackup dmb
where dmb.deliverymethodkey in (
    select oh.deliverymethodkey
    from orderheader oh
    group by oh.deliverymethodkey
    having count(distinct oh.customerkey) < 0.05 * (
        select count(distinct toh.customerkey) from orderheader toh
    )
)

-- check
select * from DeliveryMethod
minus
select * from DeliveryMethodBackup;

-- apply changes
commit;
