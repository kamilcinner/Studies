--1
select
c.customerkey as "Customer ID",
c.lastname as "Last name",
c.firstname as "First name"
from customer c
inner join orderheader oh on oh.customerkey = c.customerkey
where (oh.countrykey, oh.orderdate) = (
    select distinct
    c.countrykey,
    max(orderdate)
    from orderheader oh
    inner join country c on c.countrykey = oh.countrykey
    where c.countryname = 'Australia'
    group by c.countrykey
);

--2
select distinct
c.countryname country,
oh.orderdate as "Last order date"
from orderheader oh
inner join country c on c.countrykey = oh.countrykey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
where (psc.productcategorykey, oh.orderdate) = (
    select distinct
    psc.productcategorykey,
    max(oh.orderdate)
    from orderheader oh
    inner join orderdetail od on od.orderkey = oh.orderkey
    inner join product p on p.productkey = od.productkey
    inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
    inner join productcategory pc on pc.productcategorykey = psc.productcategorykey
    where pc.productcategoryname = 'Bikes'
    group by psc.productcategorykey
)
order by 1;

--3
select distinct
p.productname Product,
oh.orderdate as "Last order date"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join orderchannel och on och.channelkey = oh.channelkey
where (oh.channelkey, oh.orderdate) = (
    select distinct
    och.channelkey,
    max(oh.orderdate)
    from orderheader oh
    inner join orderchannel och on och.channelkey = oh.channelkey
    where och.channelname = 'Mobile application'
    and to_char(oh.orderdate, 'yyyy') = '2020'
    group by och.channelkey
);

--4
select distinct
c.customerkey as "Customer ID",
c.lastname as "Last name",
c.firstname as "First name",
oh.orderdate as "First order date"
from customer c
inner join orderheader oh on oh.customerkey = c.customerkey
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
where (psc.productcategorykey, oh.orderdate) = (
    select distinct
    pc.productcategorykey,
    min(oh.orderdate)
    from orderheader oh
    inner join orderdetail od on od.orderkey = oh.orderkey
    inner join product p on p.productkey = od.productkey
    inner join productsubcategory psc on psc.productsubcategorykey = p.productsubcategorykey
    inner join productcategory pc on pc.productcategorykey = psc.productcategorykey
    where pc.productcategoryname = 'Bikes'
    group by pc.productcategorykey
)
order by 2;

--5
select distinct
och.channelname Channel,
oh.orderdate as "Last order date"
from orderheader oh
inner join orderchannel och on och.channelkey = oh.channelkey
inner join country c on c.countrykey = oh.countrykey
inner join salesterritory st on st.salesterritorykey = c.salesterritorykey
where (c.salesterritorykey, oh.orderdate) = (
    select distinct
    st.salesterritorykey,
    max(oh.orderdate)
    from orderheader oh
    inner join orderchannel och on och.channelkey = oh.channelkey
    inner join country c on c.countrykey = oh.countrykey
    inner join salesterritory st on st.salesterritorykey = c.salesterritorykey
    where st.salesterritoryname = 'Europe'
    group by st.salesterritorykey
);
