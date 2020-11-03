<?php
include_once 'classes/User.php';

$user1 = new User(
    'luci',
    'Lucifer Morningstar',
    'lucifer@lux.com',
    'qwerty1234'
);

$user1->show();

echo '<br>';

$user2 = clone $user1;
$user2->setUsername('admin');
$user2->setStatus(User::STATUS_ADMIN);

$user2->show();