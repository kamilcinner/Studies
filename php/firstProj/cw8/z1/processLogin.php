<?php
include_once 'models/DataBase.php';
include_once 'models/UserManager.php';

$db = new DataBase('localhost:3306', 'root', '', 'users');
$userManager = new UserManager();

if (filter_input(INPUT_GET, 'action') === 'logout') {
    $userManager->logout($db);
}

if (filter_input(INPUT_POST, 'login')) {
    $userId = $userManager->login($db);
    if ($userId >= 0) {
        echo '<p>Logged in successfully!<br>';
        echo "User id is: $userId<br>";
        echo '<a href="processLogin.php?action=logout">Logout</a></p>';
    } else {
        echo '<p>Invalid login or password!</p>';
        $userManager->showLoginForm();
    }
} else {
    $userManager->showLoginForm();
}
