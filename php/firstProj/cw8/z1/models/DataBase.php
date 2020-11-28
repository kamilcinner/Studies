<?php
include_once 'User.php';

class DataBase {
    private $mysqli;
    private $db;

    public function __construct(string $server, string $user, string $pass, string $db) {
        $this->db = $db;
        $this->mysqli = new mysqli($server, $user, $pass, $db);

        if ($this->mysqli->connect_errno) {
            printf("Server connection error: %s\n", $this->mysqli->connect_error);
            exit();
        }

        $this->mysqli->set_charset("utf8");
    }

    function __destruct() {
        $this->mysqli->close();
    }

    public function getUser(string $id) {
        $query = "SELECT * FROM users WHERE id = '$id'";
        if ($result = $this->mysqli->query($query)) {
            if ($result->num_rows === 1) {
                $userObj = $result->fetch_object();
                $result->close();
                return new User(username: $userObj->username, fullName: $userObj->fullName, email: $userObj->email,
                                password: $userObj->password, status: $userObj->status, date: $userObj->date,
                                id: $userObj->id);
            }
        }
        return null;
    }

    public function getUserId(string $login=null, string $password=null, string $sessionId=null) {
        $id = -1;
        if ($login && $password) {
            $query = "SELECT * FROM users WHERE username = '$login'";
            if ($result = $this->mysqli->query($query)) {
                if ($result->num_rows === 1) {
                    $userObj = $result->fetch_object();
                    $hash = $userObj->password;
                    if (password_verify($password, $hash))
                        $id = $userObj->id;
                }
                $result->close();
            }
        } else if ($sessionId) {
            $query = "SELECT userId FROM logged_in_users WHERE sessionId = '$sessionId'";
            if ($result = $this->mysqli->query($query)) {
                if ($result->num_rows === 1) {
                    $userIdObj = $result->fetch_object();
                    $id = $userIdObj->userId;
                }
                $result->close();
            }
        }
        return $id;
    }

    public function deleteUser(string $login) {
        $query = "delete from users where username = '$login'";
        if ($this->mysqli->query($query)) {
            return true;
        }
        return false;
    }

    public function deleteUserLogs(string $userId=null, string $sessionId=null) {
        $deleteBy = $userId && !$sessionId ? 'userId' : 'sessionId';
        $value = $userId && !$sessionId ? $userId : $sessionId;

        $query = "delete from logged_in_users where $deleteBy = '$value'";
        if ($this->mysqli->query($query)) {
            return true;
        }
        return false;
    }

    public function saveUserLog(string $sessionId, string $userId, string $date) {
        $query = "insert into logged_in_users values ('$sessionId', '$userId', '$date')";
        if ($this->mysqli->query($query)) {
            return true;
        }
        return false;
    }
}