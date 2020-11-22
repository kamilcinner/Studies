<?php
include_once 'models/DataBase.php';
include_once 'models/UserStatus.php';
include_once 'models/User.php';
include_once 'models/RegistrationForm.php';

$db = new DataBase("localhost:3306", "root", "", "users");

$registrationForm = new RegistrationForm();

if (filter_input(INPUT_POST, 'submit', FILTER_SANITIZE_FULL_SPECIAL_CHARS)) {
    $user = $registrationForm->validateUser(true);
    if ($user) {
        echo '<p style="color: green;">Registration successful!</p>';
        $user->save($db);
    } else {
        echo '<p style="color: red;">Registration failed!</p>';
    }
}

echo '<h2>Registered users</h2>';
echo User::getAll($db);
