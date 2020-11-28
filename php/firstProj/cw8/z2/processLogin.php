<?php
include_once '../z1/models/DataBase.php';
include_once '../z1/models/UserManager.php';

$db = new DataBase('localhost:3306', 'root', '', 'users');
$userManager = new UserManager();

if (filter_input(INPUT_GET, 'action') === 'logout') {
    $userManager->logout($db);
}

if (filter_input(INPUT_POST, 'login')) {
    $userId = $userManager->login($db);
    if ($userId >= 0) {
        header('location:testLogin.php');
    } else {
        echo '<p>Invalid login or password!</p>';
        $userManager->showLoginForm();
    }
} else {
    $userManager->showLoginForm();
}
