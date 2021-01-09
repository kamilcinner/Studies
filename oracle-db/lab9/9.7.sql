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
create table ProductBackup as select * from Product;

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

-- check
select * from Product
minus
select * from ProductBackup;

-- apply changes
commit;

--3
