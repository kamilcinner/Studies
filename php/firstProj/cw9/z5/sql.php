<?php
include_once 'Baza.php';
$ob = new Baza('localhost:3306','root','','test');
if (isset($_POST['id']))
{
    echo 'Wybrany:<br />';
//    $id=$_POST['id'];
//    $id=addslashes($_POST['id']);
    $id=$ob->protect_string($_POST['id']);
    echo 'SQL: SELECT tytul FROM strony WHERE id="'.$id.'";<br />';
    echo $ob->select('SELECT id,tytul FROM strony WHERE id="'.$id.'";',array('id','tytul'));
}
else
{
    echo '<form action="sql.php" method="post">';
    echo 'Wpisz numer ID do pokazania: <input type="text" name="id">';
    echo '<input type="submit" value="Uruchom"><br />';
    echo 'Wszystkie:<br />';
    echo $ob->select('SELECT id,tytul FROM strony;',array('id','tytul'));
}