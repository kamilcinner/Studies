--7.4.1
select distinct
c.countryname Country,
oc.channelName as "Order channel"
from orderHeader oh
inner join orderChannel oc on oh.channelKey = oc.channelKey
right join country c on c.countryKey = oh.countryKey
order by 1;

--7.4.2
select distinct
ch.channelname,
pm.paymentmethodname
from orderheader oh
inner join paymentmethod pm on oh.paymentmethodkey = pm.paymentmethodkey
right join orderchannel ch on oh.channelkey = ch.channelkey;

--7.4.3
select distinct
c.customerkey,
c.lastname,
c.firstname,
ch.channelname
from orderchannel ch
inner join orderheader oh on ch.channelkey = oh.channelkey
right join customer c on c.customerkey = oh.customerkey
where c.lastname = 'Alan';
