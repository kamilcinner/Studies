<?php
include_once '../z1/models/DataBase.php';
include_once '../z1/models/UserManager.php';
include_once '../z1/models/User.php';
session_start();

$db = new DataBase('localhost:3306', 'root', '', 'users');
$userManager = new UserManager();

$userId = $userManager->getLoggedInUserId($db, session_id());

if ($userId >= 0) {
    $user = $db->getUser($userId);
    echo '<p>Logged in successfully!</p>';
    $user->showUserData();
    echo '<p><a href="processLogin.php?action=logout">Logout</a></p>';
} else {
    header('location:processLogin.php');
}

