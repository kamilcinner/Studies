<?php

require_once('src/classes/Site.php');
$currentSite = new Site();

$site = filter_input(INPUT_GET, 'site');
switch ($site) {
    case 'gallery':
        $site = 'gallery';
        break;
    case 'form':
        $site = 'form';
        break;
    case 'about':
        $site = 'about';
        break;
    default:
        $site = 'home';
}


$file = "src/" . $site . ".php";
if (file_exists($file)) {
    require_once($file);
    $currentSite->setTitle($title);
    $currentSite->setContent($content);
    $currentSite->show();
}
