<?php
include_once '../z2/models/User.php';
include_once '../z2/models/UserStatus.php';
include_once 'utils.php';
session_start();

$user = new User('kubus', 'Kubus Puchatek', 'kubus@stumilowylas.pl', 'xyz');
$user->setStatus(UserStatus::STATUS_ADMIN);

$_SESSION['user'] = serialize($user);

echo 'sID: ' . session_id();
printUser($user);
echo "<br>cookie: ";
var_dump(session_get_cookie_params());

echo '<br><a href="test2.php">go2</a>';