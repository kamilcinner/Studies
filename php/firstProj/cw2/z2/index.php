<?php

$students = [
    12345 => 'Smith Mazikeen',
    53896 => 'Lopez Ella',
    53947 => 'Martin Linda',
    13846 => 'Savage Adam',
    92374 => 'Hyneman Jamie'
];

function printStudents($associatedArray) {
    foreach ($associatedArray as $key => $value) {
        echo "$key - $value<br>";
    }
    echo "<br><br>";
}

// a
printStudents($students);

// b
echo "key sort<br>";
ksort($students);
printStudents($students);

// c
echo "surname sort<br>";
asort($students);
printStudents($students);

// d
echo "array push doesn't work<br>";
// array_push($students, [51054 => 'Lucifer Morningstar']);
echo "array merge<br>";
array_merge($students, [51054 => 'Lucifer Morningstar']);
printStudents($students);

// e
function shuffle_assoc($my_array) {
    $keys = array_keys($my_array);

    shuffle($keys);

    foreach($keys as $key) {
        $new[$key] = $my_array[$key];
    }

    $my_array = $new;

    return $my_array;
}
?>
<head>
    <title>Table</title>
    <style>
        table, th, td {
            border: 1px solid black;
            border-collapse: collapse;
        }
    </style>
</head>
<body>
<table>
    <tr>
        <th>Index</th>
        <th>Name</th>
    </tr>
    <?php
    $students += [51054 => 'Lucifer Morningstar'];
    $students = shuffle_assoc($students);
    foreach ($students as $key => $value) {
        echo "<tr><td>$key</td><td>$value</td></tr>";
    }
    ?>
</table>
</body>