--7.2.1
select distinct
pm.paymentMethodName as "Payment method"
from paymentMethod pm
inner join orderHeader oh on pm.paymentMethodKey = oh.paymentMethodKey
inner join orderChannel oc on oc.channelKey = oh.channelKey
where oc.channelName = 'Mobile application';

--7.2.2
select distinct
c.customerkey as "Identyfikator",
c.lastname as "Nazwisko",
c.firstname as "Imie"
from orderstatus os
inner join orderheader oh on os.orderstatuskey = oh.orderstatuskey
inner join customer c on oh.customerkey = c.customerkey
inner join orderdetail od on oh.orderkey = od.orderkey
inner join product p on od.productkey = p.productkey
inner join productsubcategory psc on psc.productSubcategoryKey = p.productSubcategoryKey
where os.orderstatusname = 'Canceled'
and psc.productSubcategoryName = 'Mountain Bikes'
order by 1;

--7.2.3
select distinct
c.customerkey,
c.lastname,
c.firstname,
p.productkey,
p.productname
from customer c
inner join orderheader oh on c.customerkey = oh.customerkey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
where c.lastname = 'Alan'
order by 1, 4;

--7.2.4
select distinct
dm.deliverymethodname
from deliverymethod dm
inner join orderheader oh on dm.deliverymethodkey = oh.deliverymethodkey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
where lower(p.productname) like '%shorts%';

--7.2.5
select distinct
to_char(oh.orderdate, 'YYYY') as "Year",
st.salesterritoryname,
p.productcode || ' - ' || p.productname as "Product"
from salesterritory st
inner join country c on c.salesterritorykey = st.salesterritorykey
inner join orderheader oh on oh.countrykey = c.countrykey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
order by 1, 2, 3;

--7.2.6
select distinct
c.customerkey,
c.lastname,
c.firstname
from customer c
inner join orderheader oh on c.customerkey = oh.customerkey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
inner join productcategory pc on pc.productCategoryKey = psc.productCategoryKey
where pc.productCategoryName = 'Bikes'
order by c.customerkey;

--7.2.7
select distinct
to_char(oh.orderdate, 'YYYY') as "Year",
case
    when to_char(oh.orderdate, 'mm') <= 3 then 'Q1'
    when to_char(oh.orderdate, 'mm') <= 6 then 'Q2'
    when to_char(oh.orderdate, 'mm') <= 9 then 'Q3'
    else 'Q4'
end as "Quarter"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
inner join productcategory pc on pc.productCategoryKey = psc.productCategoryKey
where pc.productCategoryName = 'Bikes'
order by "Year" desc, "Quarter" asc;
