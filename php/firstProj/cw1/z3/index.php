<?php

date_default_timezone_set("Europe/Warsaw");

print("timezone: ".date_default_timezone_get()."<br><br>");

$variables = new ArrayObject();

$int = 134;
$float = 67.67;
$intTrue = 1;
$intFalse = 0;
$booleanTrue = true;
$string1 = "0";
$string2 = "Typy w PHP";
$arrayInt = [1, 2, 3, 4];
$arrayEmpty = [];
$arrayString = ["zielony", "czerwony", "niebieski"];
$dateTime = new DateTime();

$variables->append(['int', $int]);
$variables->append(['float', $float]);
$variables->append(['intTrue', $intTrue]);
$variables->append(['intFalse', $intFalse]);
$variables->append(['booleanTrue', $booleanTrue]);
$variables->append(['string1', $string1]);
$variables->append(['string2', $string2]);
$variables->append(['arrayInt', $arrayInt]);
$variables->append(['arrayEmpty', $arrayEmpty]);
$variables->append(['arrayString', $arrayString]);
$variables->append(['dateTime', $dateTime]);

// a
function printVariableInfo($var) {
    $name = $var[0];
    $value = $var[1];
    print("$name = ");
    if (is_array($value)) {
        foreach ($value as $e) {
            print("$e ");
        }
        print("<br>print_r: ");
        print_r($value);
        print("<br>var_dump: ");
        var_dump($value);
    } else {
        if ($name === 'dateTime') {
            print($value->format("d.m.Y H:i"));
        } else {
            print($value);
        }
    }
    print("<br>");

    if (is_bool($value)) print("bool ");
    if (is_int($value)) print("int ");
    if (is_numeric($value)) print("numeric ");
    if (is_string($value)) print("string ");
    if (is_array($value)) print("array ");
    if (is_object($value)) print("object ");

    print("<br><br>");
}
foreach ($variables as $item) {
    printVariableInfo($item);
}

print("0 == false: ".($intFalse == false)."<br>");
print("0 === false: ".($intFalse === false));
