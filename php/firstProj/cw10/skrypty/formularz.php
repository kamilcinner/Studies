<?php
//pomocnicza funkcja generująca formularz:
function drukuj_form(){
    $form= '<h3> Formularz zamówienia:</h3>'.
        '<form method="post" action="?strona=formularz" >';
    $form.='...';
    return $form; //wynik typu String – gotowy formularz
}
//uchwyt do bazy testowa:
include_once "klasy/Baza.php";
$ob = new Baza("localhost:3306", "root", "", "clients");
$tytul = "Formularz";
$zawartosc = drukuj_form();
if (isset($_POST['pokaz'])) {
    $zawartosc.= $ob->select("select Surname,LanguageOrder from clients",
        array("Surname", "LanguageOrder"));
}
else if (isset($_POST['java'])) {
    $zawartosc.= $ob->select("select Surname,LanguageOrder from clients
        where LanguageOrder regexp 'Java'", array("Surname", "LanguageOrder"));
} else
    if (isset($_POST['dodaj'])) {
//pobierz dane z formularza
//dokonaj ich konwersji i walidacji
//sformułuj zapytanie insert i wywołaj metodę:
//$ob->insert($sql) or die("Nie udało się zapisać danych do bazy!");
}
