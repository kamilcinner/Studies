<?php session_start();

if (isset($_POST['fiber_block_number']))
{
    $_SESSION['fbn'] = $_POST['fiber_block_number'];
}

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

require_once 'func_getFibers.php';

?>

<!DOCTYPE html>
<html lang="pl">

<head>
	<meta charset="utf-8" />
	<meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" />
	
	<title>Włóczkowo</title>
	<meta name="description" content="Moje włóczki" />
    <meta name="keywords" content="blog, włóczki, sznurek" />
    <meta name="author" content="Kamil Cinner">
    
    <link href="https://fonts.googleapis.com/css?family=Akronim&display=swap&subset=latin-ext" rel="stylesheet">
    <link href="https://fonts.googleapis.com/css?family=Farsan&display=swap&subset=latin-ext" rel="stylesheet">

    <link href="main.css" rel="stylesheet" type="text/css"/>
    <link rel="stylesheet" href="css/fontello.css">

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="jquery.scrollTo.min.js"></script>
    <script src="scroll.js"></script>

    <script>

    var newHTML = "";
    var fbn = 1;
    var db_fibers_end = '0';

    function loadFibers()
    {   
        if (db_fibers_end == '1')
        {
            <?php unset($_SESSION['db_fibers_end']); ?>
            return;
        }

        var dataToSend = 'fiber_block_number=' + fbn;

        $.ajax({
            url: 'load_fibers.php',
            type: 'POST',
            data: dataToSend,
            async: true,
            success: function(data){alert(data)}
        });

        <?php require 'load_fibers.php'; ?>

        alert('<?= $_SESSION['fbn']; ?>');

        var loadedFibers = "<?php
            foreach (getFibers() as $fiber)
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

        newHTML += '<div class="fiber_block_new" id="fiber_block_' + fbn + '">' + loadedFibers + '</div>'

        document.getElementById('newest').innerHTML =
            newHTML +
            '<div onclick="loadFibers()" id="show_more">' +
                '<p>Pokaż kolejne</p>' +
            '</div>'
        ;

        //$("#fiber_block_" + fbn).css('height', '440px');
        $("#fiber_block_" + fbn).fadeIn(1000);
        $("#fiber_block_" + fbn).addClass('fiber_block');
        $("#fiber_block_" + fbn).removeClass('fiber_block_new');
        //$("#fiber_block_" + fbn + " .fiber").css('display', 'inline-block');

        db_fibers_end = '<?= isset($_SESSION['db_fibers_end']) ? '1' : '0'; ?>';
        if (db_fibers_end == '0')
        {
            $("#show_more").fadeIn(1000);
            $("#show_more").css('display', 'inline-block');
        }
    
        fbn++;
    }

    </script>
</head>

<body onload="loadFibers()">
    <header>
        <div class="logo"><a href="index.php">Włóczkowo</a></div>

        <a href="#" class="scrollup"></a>

        <nav id="topnav">
            <ul class="menu">
                <li><a href="#">Aktualności</a></li>
                <li><a href="#">Moje włóczki</a></li>
                <li><a href="#">Moje prace</a></li>
                <li><a href="#">Kontakt</a></li>
            </ul>
        </nav>
    </header>
    
    <main>
        <article>
            <section id="newest"></section>
        </article>
    </main>

    <footer>
        <div class="socials">
			<div class="socialdivs">
                <a href="#">
                    <div class="fb">
					    <i class="icon-facebook-official"></i>
				    </div>
                </a>
				
                <a target="_blank" href="https://www.instagram.com/wloczkowo/">
                    <div class="ig">
                        <i class="icon-instagram"></i>
                    </div>
                </a>
                
				<div style="clear:both"></div>
			</div>
        </div>
        
		<div class="info">
            Wszelkie prawa zastrzeżone &copy; 2019 Dziękuję za wizytę!
            <br/>
            Wykonał Kamil Cinner
		</div>
    </footer>
</body>

</html>