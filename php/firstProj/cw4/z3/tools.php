<?php
include_once 'utils/saveToFile.php';
include_once 'utils/loadFromFile.php';

$schema = ["C ", "C++", "Java ", "C#", "Html", "CSS", "XML", "PHP", "JavaScript"];

if (filter_input(INPUT_POST, 'submit')) {
    main();
}

function main() {
    global $schema;
    $regexTech = '(C|C++|Java|C#|Html|CSS|XML|PHP|JavaScript)';
    $chosenLangs = filter_input(
        INPUT_POST,
        'tech',
        FILTER_VALIDATE_REGEXP,
        [
            'flags' => FILTER_FORCE_ARRAY,
            'options' => [
                'regexp' => $regexTech
            ]
        ]
    );

    if ($chosenLangs) {
        //echo '<h1 style="color: green;">Validation success</h1>';
        //var_dump($chosenLangs);
        //echo '<br>';

        $langs = loadFromFile($schema);
        //var_dump($langs);
        //echo '<br>';
        foreach ($chosenLangs as $choice) {
            $langs[$choice]++;
        }

        saveToFile(prepareDataToSave($langs));
        redirectToStats();
    } else echo '<h1 style="color: red;">Validation error</h1>';
}

function prepareDataToSave($data) {
    $prettyData = '';
    foreach ($data as $lang => $count) {
        $prettyData .= "$count $lang\n";
    }
    return $prettyData;
}

function redirectToStats() {
    header('Location: stats.php');
    exit;
}
