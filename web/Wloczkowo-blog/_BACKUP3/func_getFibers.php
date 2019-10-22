<?php

function getFibers()
{
    echo 'numerek = '.$_SESSION['fbn'];

    require_once 'database.php';

    $block_size = 3;
            
    $fibersQuery = $db->prepare('SELECT * FROM fibers WHERE id <= :border_top AND id >= :border_bottom');
    $fibersQuery->bindValue(':border_top', $_SESSION['fbn'] * $block_size, PDO::PARAM_INT);
    $fibersQuery->bindValue(':border_bottom', $_SESSION['fbn'] * $block_size - ($block_size - 1), PDO::PARAM_INT);
    $fibersQuery->execute();

    if ($fibersQuery->rowCount() < $block_size)
    {
        $_SESSION['db_fibers_end'] = true;
    }

    return $fibersQuery->fetchAll();
}