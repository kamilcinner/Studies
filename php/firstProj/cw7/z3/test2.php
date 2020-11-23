<?php
include_once '../z2/models/User.php';
include_once 'utils.php';
session_start();

$user = unserialize($_SESSION['user']);

echo 'sID: ' . session_id();
printUser($user);
echo '<br><a href="test1.php">go1</a>';

session_destroy();