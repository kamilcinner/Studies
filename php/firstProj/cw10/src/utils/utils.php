<?php

$db = new DataBase("localhost:3306", "root", "", "clients");

function add(): string {
    $resultToShow = '';
    $resultToShow .= '<h2>Validation info</h2>';
    $resultToShow .= validateData();
    return $resultToShow;
}

function delete(): void {
    global $db;
    $db->delete();
}

function show(): string {
    global $db;
    return $db->select();
}

function showOrder(string $lang): string {
    global $db;
    return $db->select($lang);
}

function showStats(): string {
    global $db;
    $ordersCount = $db->getOrdersCountByAge();
    $ordersLess18 = $db->getOrdersCountByAge('< 18');
    $ordersMore50 = $db->getOrdersCountByAge('> 50');

    $resultToShow = '';

    $resultToShow .= "Liczba wszystkich zamówień: $ordersCount<br>";
    $resultToShow .= "Zamówienie od osób poniżej 18 lat: $ordersLess18<br>";
    $resultToShow .= "Zamówienie od osób powyżej 50 lat: $ordersMore50<br>";

    return $resultToShow;
}

function validateData(): string {
    global $db;

    $regex = [
        'lastname' => '/^[A-Z]{1}[a-ząęłńśćźżó-]{1,25}$/',
        'country' => '(Polska|Niemcy|Wielka Brytania|Czechy)',
        'tech' => '(Java|PHP|CPP)',
        'payment' => '(Visa|Master Card|Przelew)'
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

    $resultToShow = '';

    if ($errors === '') {
        $resultToShow .= '<h3 style="color: green;">Success</h3>';
        $db->insert(
            $validatedData['lastname'],
            $validatedData['age'],
            $validatedData['country'],
            $validatedData['email'],
            $validatedData['tech'],
            $validatedData['payment'],
        );
    } else {
        $resultToShow .= '<h3 style="color: red;">Fail</h3>';
        $resultToShow .= '<br>Bad data provided: ' . $errors;
    }

    return $resultToShow;
}
