<?php
include_once 'DataBase.php';

class UserManager {
    private const REGEX = [
        'username' => '/^[0-9A-Za-ząęłńśćźżó_-]{2,25}$/',
        'password' => '/^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$/'
    ];

    function showLoginForm() {
        ?><h3>Login form</h3>
        <form action="processLogin.php" method="post">
            <label for="id_username">Username:</label><br>
            <input id="id_username" name="username" value="kamil"><br>
            <label for="id_password">Password:</label><br>
            <input id="id_password" type="password" name="password" value="!Qwerty1"><br>
            <input type="submit" value="Login" name="login" />
        </form><?php
    }
    function login(DataBase $db) {
        $userId = -1;
        $validationParams = [
            'username' => [
                'filter' => FILTER_VALIDATE_REGEXP,
                'options' => [
                    'regexp' => UserManager::REGEX['username']
                ]
            ],
            'password' => [
                'filter' => FILTER_VALIDATE_REGEXP,
                'options' => [
                    'regexp' => UserManager::REGEX['password']
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
            $login = $validatedUser['username'];
            $password = $validatedUser['password'];
            $userId = $db->getUserId(login: $login, password: $password);
        } else {
            echo "<p>Invalid data provided for fields: $errors</p>";
        }

        if ($userId >= 0) {
            session_start();
            $db->deleteUserLogs(userId: $userId);
            $date = new DateTime();
            $date = $date->format('Y-m-d H:i:s');
            $sessionId = session_id();
            $db->saveUserLog($sessionId, $userId, $date);
        }
        return $userId;
    }

    function logout(DataBase $db) {
        session_start();
        $sessionId = session_id();
        if (isset($_COOKIE[session_name()])) {
            setcookie(session_name(), '', time() - 42000, '/');
        }
        session_destroy();
        $db->deleteUserLogs(sessionId: $sessionId);
    }

    function getLoggedInUserId(DataBase $db, string $sessionId) {
        return $db->getUserId(sessionId: $sessionId);
    }
}