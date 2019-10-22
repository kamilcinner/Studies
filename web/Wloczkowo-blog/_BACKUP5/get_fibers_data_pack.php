<?php

require_once 'error_report.php';

$fbn = $_POST['fiber_block_number'];

require_once 'database.php';

$block_size = 8;
            
$fibersQuery = $db->prepare('SELECT * FROM fibers WHERE id <= :border_top AND id >= :border_bottom');
$fibersQuery->bindValue(':border_top', $fbn * $block_size, PDO::PARAM_INT);
$fibersQuery->bindValue(':border_bottom', $fbn * $block_size - ($block_size - 1), PDO::PARAM_INT);
$fibersQuery->execute();

if ($fibersQuery->rowCount() == 0)
{
    echo "db_fibers_end";
}
else
{
    foreach ($fibersQuery->fetchAll() as $fiber)
    {
        echo
        "<div class='fiber' onclick='viewFiber({$fiber['id']})'>".
            "<figure>".
                "<img src='{$fiber['img_path']}' alt='{$fiber['alt']}'/>".
                "<figcaption>{$fiber['title']}</figcaption>".
            "</figure>".
        "</div>";
    }
}