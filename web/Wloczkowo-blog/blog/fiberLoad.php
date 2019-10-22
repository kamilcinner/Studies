<?php
require_once 'errorReport.php';

$id = $_POST['id'];

require_once 'database.php';
            
$fibersQuery = $db->prepare('SELECT * FROM fibers WHERE id = :id');
$fibersQuery->bindValue(':id', $id, PDO::PARAM_INT);
$fibersQuery->execute();

if ($fibersQuery->rowCount() == 1)
{
    $fiber = $fibersQuery->fetch(PDO::FETCH_ASSOC);
    echo
    "<header id='title'>{$fiber['title']}</header>".
    "<section id='fiber_description'>".
        "<img src='{$fiber['img_path']}' alt='{$fiber['alt']}'/>".
        "<p>{$fiber['description']}</p>".
    "</section>".
    "<section id='comments'>Sekcja komentarzy</section>";
}
else echo "";