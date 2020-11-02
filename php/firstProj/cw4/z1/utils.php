<?php
function add() {
    echo '<h2>Validation info</h2>';
    validateData();
}

function show() {
    $data = file(getRootPath().'data.txt');
    echo '<h2>Form data:</h2>';
    foreach ($data as $row) {
        echo "$row<br>";
    }
}

function showOrder($lang) {
    $lang = ' '.$lang.' ';
    $langOrders = '';
    $orders = getOrders();
    foreach ($orders as $order) {
        if (strpos($order, $lang)) {
            $langOrders .= $order;
        }
    }
    echo $langOrders;
}

function showStats() {
    $ordersLess18 = 0;
    $ordersMore50 = 0;

    $orders = getOrders();
    $ordersCount = count($orders);

    foreach ($orders as $order) {
        if (getAge($order) < 18) $ordersLess18++;
        else if (getAge($order) > 50) $ordersMore50++;
    }

    echo "Liczba wszystkich zamówień: $ordersCount<br>";
    echo "Zamówienie od osób poniżej 18 lat: $ordersLess18<br>";
    echo "Zamówienie od osób powyżej 50 lat: $ordersMore50<br>";
}

function validateData() {
    $regex = [
        'lastname' => '/^[A-Z]{1}[a-ząęłńśćźżó-]{1,25}$/',
        'country' => '(pl)',
        'tech' => '(C|C++|Java|C#|Html|CSS|XML|PHP|JavaScript)',
        'payment' => '(ec|vs|pb)'
    ];

    $args = [
        'lastname' => [
            'filter' => FILTER_VALIDATE_REGEXP,
            'options' => [
                'regexp' => $regex['lastname']
            ]
        ],
        'age' => [
            'filter' => FILTER_VALIDATE_INT
        ],
        'country' => [
            'filter' => FILTER_VALIDATE_REGEXP,
            'options' => [
                'regexp' => $regex['country']
            ]
        ],
        'email' => [
            'filter' => FILTER_VALIDATE_EMAIL
        ],
        'tech' => [
            'filter' => FILTER_VALIDATE_REGEXP,
            'flags' => FILTER_FORCE_ARRAY,
            'options' => [
                'regexp' => $regex['tech']
            ],
        ],
        'payment' => [
            'filter' => FILTER_VALIDATE_REGEXP,
            'options' => [
                'regexp' => $regex['payment']
            ]
        ]
    ];

    $validatedData = filter_input_array(INPUT_POST, $args);

    var_dump($validatedData);

    $errors = '';
    foreach ($validatedData as $key => $value) {
        if (!$value) {
            $errors .= $key . ', ';
        }
    }

    if ($errors === '') {
        echo '<h3 style="color: green;">Success</h3>';
        prepareDataToSave('data.txt', $validatedData);
    } else {
        echo '<h3 style="color: red;">Fail</h3>';
        echo '<br>Bad data provided: ' . $errors;
    }
}

function getOrders() {
    $data = file(getRootPath() . 'data.txt');
    $orders = [];
    $currentOrder = '';
    foreach ($data as $index => $row) {
        if ($row === "\n") {
            if ($index > 0 and $data[$index - 1] === "\n") continue;
            array_push($orders, $currentOrder . "<br>");
            $currentOrder = '';
            continue;
        }
        $currentOrder .= "$row<br>";
    }
    return $orders;
}

function getAge($order) {
    $ageLinePos = 1;
    $agePos = 10;
    $age = '';
    foreach (preg_split("/((\r?\n)|(\r\n?))/", $order) as $index => $line) {
        if ($index === $ageLinePos) {
            while ($agePos < strlen($line)) {
                $age .= $line[$agePos];
                $agePos++;
            }
            break;
        }
    }
    return intval($age);
}

function prepareDataToSave($fileName, $data) {
    $translation = [
        'lastname' => 'Nazwisko',
        'age' => 'Wiek',
        'country' => 'Państwo',
        'email' => 'Adres email',
        'tech' => 'Technologie',
        'payment' => 'Sposób zapłaty'
    ];

    $prettyData = '';
    foreach ($data as $key => $value) {
        if (is_array($value)) {
            $prettyData .= "$translation[$key]: ";
            foreach ($value as $item) {
                $prettyData .= "$item ";
            }
            $prettyData .= "\n";
        }
        else {
            $prettyData .= "$translation[$key]: $value\n";
        }
    }
    $prettyData .= "\n";

    saveToFile($fileName, $prettyData);
}

function saveToFile($fileName, $data) {
    $file = fopen(getRootPath().$fileName, 'a');
    fwrite($file, $data);
    fclose($file);
}

function printServerArray() {
    echo "<h2>Server array</h2>";
    foreach ($_SERVER as $item) {
        echo "$item<br>";
    }
}

function getRootPath() {
    return $_SERVER['DOCUMENT_ROOT'].'/';
}
