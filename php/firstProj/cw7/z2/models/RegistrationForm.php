<?php

class RegistrationForm {
    private const REGEX = [
        'username' => '/^[0-9A-Za-ząęłńśćźżó_-]{2,25}$/',
        'fullName' => '/^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð ,.\'-]+$/u',
        'password' => '/^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$/'
    ];

    protected User|null $user;

    function __construct() {
    ?>
        <h3>Registration form</h3>
        <form action="/cw7/z2/index.php" method="post">
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
        $validationParams = [
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
            ],
            'email' => [
                'filter' => FILTER_VALIDATE_EMAIL
            ],
            'password' => [
                'filter' => FILTER_VALIDATE_REGEXP,
                'options' => [
                    'regexp' => RegistrationForm::REGEX['password']
                ]
            ]
        ];

        $validatedUser = filter_input_array(INPUT_POST, $validationParams);

        $errors = '';
        foreach ($validatedUser as $key => $value) {
            if (!$value) {
                $errors .= $key . ', ';
            }
        }

        if ($errors === '') {
            // No errors
            $this->user = new User(
                $validatedUser['username'],
                $validatedUser['fullName'],
                $validatedUser['email'],
                $validatedUser['password']
            );
        } else {
            echo "<p>Invalid data provided for fields: $errors</p>";
            $this->user = null;
        }

        return $this->user;
    }
}
