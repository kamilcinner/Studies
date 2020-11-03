<?php

class RegistrationForm {
    const REGEX = [
        'username' => '/^[0-9A-Za-ząęłńśćźżó_-]{2,25}$/',
        'fullName' => '',
    ];

    protected $user;

    function __construct() {
    ?>
        <h3>Registration form</h3>
        <form action="../index.php" method="post">
            <label for="id_username">Username:</label><br>
            <input id="id_username" name="username"><br>
            <label for="idFullName">Full name:</label><br>
            <input id="idFullName" name="fullName"><br>
            <label for="idEmail">Email:</label><br>
            <input id="idEmail" type="email" name="email"><br>
            <label for="idPassword">Password:</label><br>
            <input id="idPassword" type="password" name="password"><br>
            <input type="submit" value="Register" name="submit">
        </form>
    <?php
    }

    function validateUser() {
        $args = [
            'username' => [
                'filter' => FILTER_VALIDATE_REGEXP,
                'options' => [
                    'regexp' => RegistrationForm::REGEX['username']
                ]
            ],
            'fullName' => [
                'filter' => FILTER_VALIDATE_REGEXP,
                'options' => [
                    'regexp' => RegistrationForm::REGEX['fullName']
                ]
            ]
        ];
    }
}
