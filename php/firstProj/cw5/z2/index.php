<?php
include_once '../z1/models/User.php';
include_once 'models/RegistrationForm.php';

$registrationForm = new RegistrationForm();

if (filter_input(INPUT_POST, 'submit', FILTER_SANITIZE_FULL_SPECIAL_CHARS)) {
    $user = $registrationForm->validateUser();
    if ($user) {
        echo '<p style="color: green;">Registration successful</p>';
        $user->show();
    } else {
        echo '<p style="color: red;">Invalid registration data</p>';
    }
}