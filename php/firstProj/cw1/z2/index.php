<?php

function gallery($rows, $cols) {
    $max = $rows * $cols;

    if ($max > 10) {
        return;
    }

    for ($i = 1; $i <= $max; $i++) {
        $name = "obraz$i";
        print("<img src='z2/obrazki/$name.JPG' alt='$name' />");
        if ($i % $cols === 0) {
            print("<br>");
        }
    }
    print("<br>");
}

gallery(3, 3);
gallery(4, 2);
gallery(2, 4);
