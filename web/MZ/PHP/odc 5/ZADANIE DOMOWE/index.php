<?php session_start();?>
<!DOCTYPE html>
<html lang="pl">
<head>
    <meta charset="utf-8">
    <title>Newsletter - zapisz się!</title>
    <meta name="description" content="Używanie PDO - zapis do bazy MySQL">
    <meta name="keywords" content="php, kurs, PDO, połączenie, MySQL">
    <meta http-equiv="X-Ua-Compatible" content="IE=edge">

    <link rel="stylesheet" href="main.css">
    <link href="https://fonts.googleapis.com/css?family=Lobster|Open+Sans:400,700&amp;subset=latin-ext" rel="stylesheet">
    <!--[if lt IE 9]>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/html5shiv/3.7.3/html5shiv.min.js"></script>
    <![endif]-->
    <script src='https://www.google.com/recaptcha/api.js'></script>
</head>

<body>
    <div class="container">

        <header>
            <h1>Newsletter</h1>
        </header>

        <main>
            <article>
                <form method="post" action="save.php">
                    <label>Enter email address
                        <input type="email" name="email" <?= isset($_SESSION['given_email']) ? 'value="'.$_SESSION['given_email'].'"' : '' ?>>
                    </label>
                    
                    <?php
                        if (isset($_SESSION['err_email'])) {
                            echo "<p>{$_SESSION['err_email']}</p>";
                            unset($_SESSION['err_email']);
                        }
                        if (isset($_SESSION['errE_email'])) {
                            echo "<p>{$_SESSION['errE_email']}</p>";
                            echo "<p><a href='delete.php'>Unregister this email</a></p>";
                            unset($_SESSION['errE_email']);
                        }

                    ?>

                    <div class="captcha">
                        <div class="g-recaptcha" data-sitekey="6LcnKnMUAAAAAMc43WZzkgLlqIPhGgla--454eN9"></div>
                        <?php
                        if (isset($_SESSION['err_bot'])) {
                            echo '<br /><br /><div class="error">'.$_SESSION['err_bot'].'</div>';
                            unset($_SESSION['err_bot']);
                        }
                        ?>
                    </div>

                    <input type="submit" value="Zapisz się!">
                </form>
            </article>
        </main>

    </div>
</body>
</html>