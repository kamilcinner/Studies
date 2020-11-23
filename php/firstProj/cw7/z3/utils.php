<?php
include_once '../z2/models/User.php';
function printUser(User $user) {
    echo '<br>Username: ' . $user->getUsername();
    echo '<br>Full name: ' . $user->getFullName();
    echo '<br>Email: ' . $user->getEmail();
    echo '<br>Status: ';
    echo $user->getStatus() === UserStatus::STATUS_ADMIN ? 'ADMIN' : 'USER';
}