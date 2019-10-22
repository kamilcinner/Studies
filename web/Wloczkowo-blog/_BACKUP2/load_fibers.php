<?php

class FiberBlock
{   
    public $fiber_block_number = 1;
    static public $new_fiber_block = true;
    public $fibers = "";

    private $block_size = 3;

    public function getFibers()
    {
        require_once 'database.php';
            
        $fibersQuery = $db->prepare('SELECT * FROM fibers WHERE id <= :border_top AND id >= :border_bottom');
        $fibersQuery->bindValue(':border_top', $this->fiber_block_number * $this->block_size, PDO::PARAM_INT);
        $fibersQuery->bindValue(':border_bottom', $this->fiber_block_number * $this->block_size - ($this->block_size - 1), PDO::PARAM_INT);
        $fibersQuery->execute();

        if ($fibersQuery->rowCount() < 3)
        {
            self::$new_fiber_block = false;
        }

        $this->fibers = $fibersQuery->fetchAll();
    }
}

$fiberBlock = new FiberBlock;

?>

<script>

var newHTML = "";

function loadFibers()
{   
    var checker = '<?php echo FiberBlock::$new_fiber_block; ?>';
    if (checker != '1')
    {
        $("#show_more").css('display', 'none');
        return;
    }

    var fbn = <?php echo $fiberBlock->{'fiber_block_number'}; ?>;
    <?php $fiberBlock->{'getFibers'}(); ?>

    var loadedFibers = "<?php
        foreach ($fiberBlock->{'fibers'} as $fiber)
        {
            echo
            "<a href='#'>".
                "<div class='fiber'>".
                    "<figure>".
                        "<img src='{$fiber['img_path']}' alt='{$fiber['alt']}'/>".
                        "<figcaption>{$fiber['title']}</figcaption>".
                    "</figure>".
                 "</div>".
            "</a>";
        }
    ?>";

    newHTML += '<div id="fiber_block_' + fbn + '">' + loadedFibers + '</div>'

    document.getElementById('newest').innerHTML =
        newHTML +
        '<div onclick="loadFibers()" id="show_more">' +
            '<p>Pokaż kolejne</p>' +
        '</div>'
    ;

    $("#fiber_block_" + fbn + " .fiber").fadeIn(1000);
    $("#fiber_block_" + fbn + " .fiber").css('display', 'inline-block');
    $("#show_more").fadeIn(1000);
    $("#show_more").css('display', 'inline-block');

    <?php $fiberBlock->{'fiber_block_number'}++; ?>
}

</script>
