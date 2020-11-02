<?php
include_once 'getRootPath.php';

function saveToFile($data) {
    file_put_contents(getRootPath().'form.txt', $data);
}
