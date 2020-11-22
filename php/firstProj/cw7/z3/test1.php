<?php

session_start();
$_SESSION['username'] = 'kubus';
$_SESSION['fullName'] = 'Kubus Puchatek';
$_SESSION['email'] = 'kubus@stumilowylas.pl';
$_SESSION['status'] = 'ADMIN';

echo 'sID: ' . session_id();

$names = ['username', 'fullName', 'email', 'status'];

foreach ($names as $name) {
    echo "<br>$name: " . $_SESSION[$name];
}

echo "<br>cookie: ";
var_dump(session_get_cookie_params());
