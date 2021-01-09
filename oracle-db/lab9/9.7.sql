--1
-- copy
create table CustomerBackup as select * from customer;

-- delete
delete from CustomerBackup
where customerkey not in
(
    select distinct customerkey from orderheader
);

-- check
select * from customer
minus
select * from CustomerBackup;

-- apply changes
commit;

--2
