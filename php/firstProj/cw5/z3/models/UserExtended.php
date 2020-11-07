<?php

class UserExtended extends User {
    function __construct(string $username, string $fullName, string $email, string $password) {
        parent::__construct($username, $fullName, $email, $password);
    }

    static function getAllUsers(string $filePath){
        $users = json_decode(file_get_contents($filePath));
        echo '<ul>';
        foreach ($users as $user){
            echo "<li>" . $user->username . ",<div style='left: 150px; position: fixed; display: inline-block;'>" . $user->fullName . ",</div><div style='left: 300px; position: fixed; display: inline-block;'>" . $user->date . "</div></li>";
        }
        echo '</ul>';
    }

    function toArray(){
        return [
            'username' => $this->username,
            'fullName' => $this->fullName,
            'email' => $this->email,
            'password' => $this->password,
            'status' => $this->status,
            'date' => $this->date
        ];
    }

    function save(string $filePath){
        $users = json_decode(file_get_contents($filePath),true);
        array_push($users, $this->toArray());
        file_put_contents($filePath, json_encode($users));
    }
}
