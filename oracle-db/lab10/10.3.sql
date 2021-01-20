--1
describe ALL_INDEXES;

--2
select
index_name,
index_type,
uniqueness,
num_rows,
status
from ALL_INDEXES
where lower(table_name) = 'productcategory';

--3
select
index_name,
column_name,
column_position
from ALL_IND_COLUMNS
where lower(table_name) = 'productcategory';

--4
select
index_name,
index_type,
uniqueness,
num_rows,
status
from ALL_INDEXES
where lower(table_name) = 'productsubcategory';

--5
select
index_name,
index_type,
uniqueness,
num_rows,
status
from ALL_INDEXES
where lower(table_name) = 'product';

--6
select
index_name,
index_type,
uniqueness,
num_rows,
status
from ALL_INDEXES
where lower(table_name) = 'customer';

--7
select
index_name,
column_name,
column_position
from ALL_IND_COLUMNS
where lower(table_name) = 'customer';
