<?php

class User {
    protected string $username;
    protected string|null|false $password;
    protected string $fullName;
    protected string $email;
    protected DateTime|string $date;
    protected int $status;

    function __construct(string $username, string $fullName, string $email, string $password) {
        $this->username = $username;
        $this->fullName = $fullName;
        $this->email = $email;
        $this->password = password_hash($password, PASSWORD_DEFAULT);
        $this->status = UserStatus::STATUS_USER;
        $this->date = new DateTime();
        $this->date = $this->date->format('Y-m-d');
    }

    function save(DataBase $db) {
        $data = [
            $this->username,
            $this->fullName,
            $this->email,
            $this->password,
            $this->status,
            $this->date
        ];
        $db->insert($data);
    }

    static function getAll(DataBase $db) {
        $columns = ['id', 'username', 'fullName', 'email', 'status', 'date'];
        return $db->select($columns);
    }

    /**
     * @return string
     */
    public function getUsername() {
        return $this->username;
    }

    /**
     * @param string $username
     */
    public function setUsername(string $username): void {
        $this->username = $username;
    }

    /**
     * @return string
     */
    public function getPassword() {
        return $this->password;
    }

    /**
     * @param string $password
     */
    public function setPassword(string $password): void {
        $this->password = password_hash($password, PASSWORD_DEFAULT);
    }

    /**
     * @return string
     */
    public function getFullName() {
        return $this->fullName;
    }

    /**
     * @param string $fullName
     */
    public function setFullName(string $fullName): void {
        $this->fullName = $fullName;
    }

    /**
     * @return string
     */
    public function getEmail() {
        return $this->email;
    }

    /**
     * @param string $email
     */
    public function setEmail(string $email): void {
        $this->email = $email;
    }

    /**
     * @return string
     */
    public function getDate() {
        return $this->date;
    }

    /**
     * @return int
     */
    public function getStatus() {
        return $this->status;
    }

    /**
     * @param int $status
     */
    public function setStatus(int $status): void {
        $this->status = $status;
    }
}
