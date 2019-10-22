<?php

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

/*$data = array();
if(isset($_POST['randomAnswer']) && !empty($_SERVER['HTTP_X_REQUESTED_WITH'])) {
$data = 'You number is: ' . $_POST['randomAnswer'];       
echo json_encode($data);  
die();      
}*/

$_SESSION['fbn'] = $_POST['fiber_block_number'];
// echo $_SESSION['fbn'];
// die();