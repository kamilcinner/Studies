<?php
function add() {
    $data = '';
    $namesWithTranslations = [
        ['lastname', 'Nazwisko'],
        ['age', 'Wiek'],
        ['country', 'Państwo'],
        ['email', 'Adres email'],
        ['tech', 'Technologie'],
        ['payment', 'Sposób zapłaty']
    ];
    foreach ($namesWithTranslations as $item) {
        $data .= pushFormInput($item[0], $item[1]);
    }
    $data .= "\n";
    $file = fopen(getRootPath().'data.txt', 'a');
    fwrite($file, $data);
    fclose($file);
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

function pushFormInput($name, $translation) {
    $regex = array(
        'lastname' => '/^[A-Z]{1}[a-ząęłńśćźżó-]{1,25}$/',
        'country' => '/^Polska$/'
    );


    $args = array(
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
        ]
    );

    $newData = '';
    if (isset($_REQUEST[$name]) && ($_REQUEST[$name] !== "")) {
        $value = $_REQUEST[$name];
        if (is_array($value)) {
            $newData .= "$translation: ";
            foreach ($value as $item) {
                $newData .= "$item ";
            }
            $newData .= "\n";
        }
        else {
            $value = htmlspecialchars(trim($_REQUEST[$name]));
            $newData .= "$translation: $value\n";
        }
    }
    else $newData .= "$translation was empty.\n";
    return $newData;
}

function getOrders() {
    $data = file(getRootPath().'data.txt');
    $orders = [];
    $currentOrder = '';
    foreach ($data as $row) {
        if ($row === "\n") {
            array_push($orders, $currentOrder."<br>");
            $currentOrder = '';
            continue;
        }
        $currentOrder .= "$row<br>";
    }
    return $orders;
}

function printServerArray() {
    echo "<h2>Server array</h2>";
    foreach ($_SERVER as $item) {
        echo "$item<br>";
    }
}

function getRootPath() {
    return $_SERVER['DOCUMENT_ROOT']."/";
}
