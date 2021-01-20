--1
alter table ProductCategory drop constraint ProductCategory_Name_UQ;

-- upper one is enoug
drop index ProductCategory_Name_UQ;
alter table ProductCategory
add constraint ProductCategory_Name_UQ unique (ProductCategoryName);

-- check
select
index_name,
column_name,
column_position
from ALL_IND_COLUMNS
where lower(table_name) = 'productcategory';

--2
drop index Customer_Name_IDX;

-- check
select
index_name,
column_name,
column_position
from ALL_IND_COLUMNS
where lower(table_name) = 'customer';
