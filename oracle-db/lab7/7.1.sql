--7.1.1
select
c.productCategoryName as "Category name",
sc.productSubcategoryName as "Subcategory name"
from productCategory c
inner join productSubcategory sc on c.productCategoryKey = sc.productCategoryKey
order by 1, 2 desc;

--7.1.2
select
p.productCode || '-' ||
p.productName as "Kod-Nazwa",
sc.productSubcategoryName Podkategoria
from product p
inner join productSubcategory sc on p.productSubcategoryKey = sc.productsubcategorykey
order by p.productname asc;
--7.1.3

select distinct
to_char(oh.orderdate, 'YYYY') Year,
od.productkey Product
from orderheader oh
inner join orderdetail od on oh.orderkey = od.orderkey
where to_char(oh.orderdate, 'YYYY') in ('2018', '2019')
order by 1 desc, 2;

--7.1.4
select distinct
od.productkey,
od.transactionprice
from orderdetail od
inner join orderheader oh on od.orderkey = oh.orderkey
where oh.orderdate between date '2018-12-1' and date '2018-12-24'
and oh.channelkey = 2
order by 2 desc;
