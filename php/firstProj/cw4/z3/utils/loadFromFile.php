<?php
include_once 'getRootPath.php';

/**
 * Loads languages stats from file
 * @param $schema array schema
 * @return array languages associative array
 * filled with data from file or empty if file is empty
 */
function loadFromFile(array $schema) {
    $langAssocArray = getEmptyLangAssocArray($schema);

    $data = file(getRootPath() . 'form.txt');
    foreach ($data as $line) {
        $i = 0;
        $count = '';
        while ($line[$i] !== ' ') {
            $count .= $line[$i];
            $i++;
        }
        foreach ($schema as $lang) {
            if (strpos($line, $lang)) {
                $langAssocArray[$lang] = intval($count);
                break;
            }
        }
    }
    return $langAssocArray;
}

function getEmptyLangAssocArray($schema) {
    $langAssocArray = array_flip($schema);
    foreach ($langAssocArray as $lang => $count) {
        $langAssocArray[$lang] = 0;
    }
    return $langAssocArray;
}
