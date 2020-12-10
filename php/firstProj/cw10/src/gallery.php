<?php

$title = 'Galeria';
$content = '';

foreach (range(1, 10) as $i) {
    $content .= "<img src=\"/cw10/assets/thumbnails/obraz$i.JPG\" alt=\"photo$i\">";
}
