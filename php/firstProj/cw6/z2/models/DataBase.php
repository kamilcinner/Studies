<?php

class DataBase {
    private $mysqli;

    public function __construct(string $serwer, string $user, string $pass, string $baza) {
        $this->mysqli = new mysqli($serwer, $user, $pass, $baza);

        if ($this->mysqli->connect_errno) {
            printf("Nie udało sie połączenie z serwerem: %s\n",
                $this->mysqli->connect_error);
            exit();
        }

        $this->mysqli->set_charset("utf8");
    }

    function __destruct() {
        $this->mysqli->close();
    }

    public function select(string $lang = '') {
        $query = "select Surname, LanguageOrder from clients";
        $columns = ['Surname', 'LanguageOrder'];

        if ($lang != '') {
            $query .= " where LanguageOrder regexp '$lang'";
        }

        $body = '';

        if ($result = $this->mysqli->query($query)) {
            $body .= '<table><tbody>';

            while ($row = $result->fetch_object()) {
                $body .= '<tr>';
                for ($i = 0; $i < count($columns); $i++) {
                    $col = $columns[$i];
                    $body .= '<td>' . $row->$col . '</td>';
                }
                $body.='</tr>';
            }
            $body.='</table></tbody>';

            $result->close();
        }
        return $body;
    }

    public function insert(string $surname, int $age, string $country, string $email, array $languages, string $payment) {
        $languageSet = '';

        foreach ($languages as $index => $lang) {
            if ($index === 0) {
                $languageSet .= $lang;
            } else {
                $languageSet .= ",$lang";
            }
        }
        $query = "insert into clients values (null, '$surname', '$age', '$country', '$email', '$languageSet', '$payment')";

        if ($conn = $this->mysqli->query($query)) {
            return true;
        }
        return false;
    }

    public function delete() {
        $query = 'delete from clients';
        if ($this->mysqli->query($query)) {
            return true;
        }
        return false;
    }

    public function getOrdersCountByAge(string $ageCondition = '') {
        $count = false;

        $query = "select count(Age) from clients";
        if ($ageCondition != '') {
            $query .= " where age $ageCondition";
        }

        if ($conn = $this->mysqli->query($query)) {
            $count = $conn->fetch_row();
            $conn->close();
        }
        return $count[0];
    }
}