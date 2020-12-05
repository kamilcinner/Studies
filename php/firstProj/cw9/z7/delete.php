<?php
include_once 'Baza.php';
$ob = new Baza('localhost:3306','root','','test');
if (isset($_POST['id']))
    if ($ob->delete('DELETE FROM strony WHERE id="'.
        $ob->protect_int($_POST['id']).'"'))
        echo 'Skasowano rekord o id='.$_POST['id'];
    else
        echo 'Nie można skasować rekordu!';