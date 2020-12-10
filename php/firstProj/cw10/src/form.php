<?php

include_once 'helpers/printForm.php';
include_once 'classes/DataBase.php';
include_once 'utils/utils.php';

$title = "Formularz";
$content = getForm();

$action = filter_input(INPUT_POST, 'submit');
switch ($action) {
    case "Dodaj": $content .= add(); break;
    case "Pokaz": $content .= show(); break;
    case "Java": $content .= showOrder("Java"); break;
    case "PHP": $content .= showOrder("PHP"); break;
    case "CPP": $content .= showOrder("CPP"); break;
    case "Statystyki": $content .= showStats(); break;
    case "Delete": delete(); break;
    default: {}
}
