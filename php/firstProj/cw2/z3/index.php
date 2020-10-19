<?php
$students = [
    12345 => [2,4,4,4.5,5,5,3.5],
    53896 => [3,3,3,5,5,5,4,2,4.5],
    53947 => [3,4,5],
    13846 => [2,2,3,3,5,4],
    92374 => [3.5,3,4,5,4.5]
];

foreach ($students as $key => $marks) {
    $sum = 0;
    $count = 0;
    foreach ($marks as $mark) {
        $sum += $mark;
        $count++;
    }
    $result = $sum / $count;
    echo "$key - $result<br>";
}
