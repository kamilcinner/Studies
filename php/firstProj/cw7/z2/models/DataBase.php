<?php

class DataBase {
    private $mysqli;
    private $db;

    public function __construct(string $server, string $user, string $pass, string $db) {
        $this->db = $db;
        $this->mysqli = new mysqli($server, $user, $pass, $db);

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

    public function select(array $columns) {
        $db = $this->db;
        $query = "select ";

        foreach ($columns as $index => $col) {
            if ($index === 0) {
                $query .= $col;
            } else {
                $query .= ", $col";
            }
        }
        $query .= " from $db";

        $body = '<table><tr>';
        foreach ($columns as $col) {
            $body .= "<th>$col</th>";
        }
        $body .= '</tr>';

        if ($result = $this->mysqli->query($query)) {
            $body .= '<tbody>';

            while ($row = $result->fetch_object()) {
                $body .= '<tr>';
                for ($i = 0; $i < count($columns); $i++) {
                    $col = $columns[$i];
                    $body .= '<td>' . $row->$col . '</td>';
                }
                $body.='</tr>';
            }
            $body.='</tbody>';

            $result->close();
        }
        $body .= '</table>';
        return $body;
    }

    public function insert(array $data) {
        $db = $this->db;
        $query = "insert into $db values (null";
        foreach ($data as $key => $value) {
            $query .= ", '$value'";
        }
        $query .= ")";

        echo $query;

        if ($this->mysqli->query($query)) {
            return true;
        }
        return false;
    }
}