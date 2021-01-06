--1
select
co.countryname Country,
count(distinct oh.customerkey) as "#Customers"
from country co
inner join orderheader oh on oh.countrykey = co.countrykey
where to_char(oh.orderdate, 'yyyy') = '2019'
group by co.countryname
having count(distinct oh.customerkey) > 1500
order by 2 desc;

--2
select
to_char(oh.orderdate, 'yyyy') Year,
c.customerkey as "Customer ID",
c.lastname || ' ' || c.firstname as "Customer Name",
sum(od.transactionprice * od.quantity) as "Total value"
from orderheader oh
inner join customer c on c.customerkey = oh.customerkey
inner join orderdetail od on od.orderkey = oh.orderkey
group by
to_char(oh.orderdate, 'yyyy'),
c.customerkey,
c.lastname || ' ' || c.firstname
having sum(od.transactionprice * od.quantity) > 12000
order by 1 desc, 4 desc;

--3
select
to_char(oh.orderdate, 'yyyy') Year,
och.channelname Channel,
pm.paymentmethodname as "Payment Method",
count(distinct oh.customerkey) as "#Customers"
from orderheader oh
inner join customer c on c.customerkey = oh.customerkey
inner join paymentMethod pm on pm.paymentMethodKey = oh.paymentMethodKey
inner join orderchannel och on och.channelkey = oh.channelkey
group by
to_char(oh.orderdate, 'yyyy'),
och.channelname,
pm.paymentmethodname
having count(distinct oh.customerkey) > 1300
order by 1, 2, 4;

--4
select
to_char(oh.orderdate, 'yyyy') Year,
p.productName,
count(distinct oh.customerkey) as "#Customers"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
group by
to_char(oh.orderdate, 'yyyy'),
p.productName
having count(distinct oh.customerkey) > 1000
order by 1 desc, 3 desc;

--5
select
to_char(oh.orderdate, 'yyyy') Year,
c.customerkey as "Customer ID",
c.lastname,
c.firstname,
count(distinct oh.orderkey) as "#Orders",
sum(od.transactionprice * od.quantity) as "Total value"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join customer c on c.customerkey = oh.customerkey
where oh.channelkey = '2'
group by
to_char(oh.orderdate, 'yyyy'),
c.customerkey,
c.lastname,
c.firstname
having
count(distinct oh.orderkey) > 20
and sum(od.transactionprice * od.quantity) > 800
order by 1, 5 desc;

--6
select
to_char(oh.orderdate, 'yyyy') Year,
'Q' || to_char(oh.orderdate, 'q') Quarter,
och.channelname Channel,
sum(od.transactionprice * od.quantity) as "Total value"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join orderchannel och on och.channelkey = oh.channelkey
group by
to_char(oh.orderdate, 'yyyy'),
'Q' || to_char(oh.orderdate, 'q'),
och.channelname
having sum(od.transactionprice * od.quantity) > 3000000
order by 1, 2;

--7
select
to_char(oh.orderdate, 'yyyy') Year,
c.countryname Country,
p.productName Product,
sum(od.quantity) as "#Items"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
inner join country c on c.countrykey = oh.countrykey
group by
to_char(oh.orderdate, 'yyyy'),
c.countryname,
p.productName
having sum(od.quantity) > 500
order by 1, 2, 4 desc;

--8
select
to_char(oh.orderdate, 'yyyy') Year,
to_char(oh.orderdate, 'Month') Month,
och.channelname Channel,
round(avg(od.transactionprice * od.quantity), 2) as "Avg Order Value"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join orderchannel och on och.channelkey = oh.channelkey
group by
to_char(oh.orderdate, 'yyyy'),
to_char(oh.orderdate, 'Month'),
och.channelname
having round(avg(od.transactionprice * od.quantity), 2) > 2500
order by 1, 2, 4;

--9
select
p.productName Product,
round(avg(oh.deliverydate - oh.orderdate)) as "#Days"
from orderheader oh
inner join orderdetail od on od.orderkey = oh.orderkey
inner join product p on p.productkey = od.productkey
group by p.productName
having round(avg(oh.deliverydate - oh.orderdate)) = 7;

--10
select
c.customerkey,
c.lastname,
c.firstname,
min(to_char(oh.orderdate, 'dd-mm-yyyy')) as "First Order Date"
from orderheader oh
inner join customer c on c.customerkey = oh.customerkey
group by
c.customerkey,
c.lastname,
c.firstname
having min(to_char(oh.orderdate, 'dd-mm-yyyy')) = '01-04-2019'
order by 1;

--11
select
c.customerkey as "Customer ID",
c.lastname,
c.firstname,
min(to_char(oh.orderdate, 'dd-mm-yyyy')) as "First Order",
max(to_char(oh.orderdate, 'dd-mm-yyyy')) as "Last Order",
max(oh.orderdate) - min(oh.orderdate) as "#DiffDays"
from orderheader oh
inner join customer c on c.customerkey = oh.customerkey
group by
c.customerkey,
c.lastname,
c.firstname
having max(oh.orderdate) - min(oh.orderdate) > 300
order by 6 desc;
