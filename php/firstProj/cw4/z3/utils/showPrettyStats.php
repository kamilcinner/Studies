<?php
include_once 'loadFromFile.php';

function showPrettyStats($schema) {
    $langs = loadFromFile($schema);
    foreach ($langs as $lang => $count) {
        echo "$count <div style='left: 40px; position: fixed; display: inline-block;'>$lang</div><br>";
    }
}
