<?php
include_once  '../z1/models/UserStatus.php';
include_once '../z1/models/User.php';
include_once 'models/UserExtended.php';
include_once '../z2/models/RegistrationForm.php';

$usersFilePath = 'users.json';

$registrationForm = new RegistrationForm();

if (filter_input(INPUT_POST, 'submit', FILTER_SANITIZE_FULL_SPECIAL_CHARS)) {
    $user = $registrationForm->validateUser(true);
    if ($user) {
        echo '<p style="color: green;">Registration successful!</p>';
        $user->show();
        $user->save($usersFilePath);
    } else {
        echo '<p style="color: red;">Registration failed!</p>';
    }
}

echo '<h2>Registered users</h2>';
UserExtended::getAllUsers($usersFilePath);
