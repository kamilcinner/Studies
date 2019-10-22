<?php session_start();
require_once 'errorReport.php';

if (isset($_SESSION['loggedIn']))
{
    header('Location: strona-glowna');
    exit();
}

if (isset($_POST['login']))
{
    $login = $_POST['login'];
    $pass = $_POST['pass'];

    $login = htmlentities($login, ENT_QUOTES, "UTF-8");

    require_once 'database.php';

    $userQuery = $db->prepare('SELECT * FROM users WHERE login=:login');
    $userQuery->bindValue(':login', $login, PDO::PARAM_STR);
    $userQuery->execute();
    
    if ($userQuery->rowCount() > 0)
    {
        $user = $userQuery->fetch(PDO::FETCH_ASSOC);
        if (password_verify($pass, $user['hashedPass']))
        {
            $_SESSION['loggedIn'] = true;
            $_SESSION['login'] = $user['login'];
            $_SESSION['email'] = $user['email'];
            if (isset($_SESSION['e_logging'])) unset($_SESSION['e_logging']);
            header('Location: strona-glowna');
        }
        else
        {
            $_SESSION["e_logging"] = '<span style="color: red">Nieprawidłowa nazwa użytkownika lub hasło!</span>';
        }
    }
    else
    {
        $_SESSION["e_logging"] = '<span style="color: red">Nieprawidłowa nazwa użytkownika lub hasło!</span>';
    }
}
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
    <link href="css/register.css" rel="stylesheet" type="text/css"/>
    <link rel="stylesheet" href="css/fontello.css">

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="jquery.scrollTo.min.js"></script>
    <script src="scroll.js"></script>
</head>

<body>
    <header>
        <div class="logo"><a href="strona-glowna">Włóczkowo</a></div>

        <a href="#" class="scrollup"></a>

        <nav id="topnav">
            <ul class="menu">
                <li><a href="#">Aktualności</a></li>
                <li><a href="#">Moje włóczki</a></li>
                <li><a href="moje-prace">Moje prace</a></li>
                <li><a href="#">Kontakt</a></li>
                <?= !isset($_SESSION['loggedIn']) ? '<li><a href="zaloguj">Zaloguj się</a></li>' : '<li><a href="wyloguj">Wyloguj się</a></li>' ?>
            </ul>
        </nav>
    </header>

    <main>
        <article id="content">
            <div id="logging-panel">
                <header>Zaloguj się</header>
                <a href="zarejestruj-konto">Nie masz jeszcze konta? - Zarejestruj się</a>
                <br/><br/>

                <form method="post">
                    Nazwa użytkownika: <br/><input type="text" name="login"/><br/>
                    Hasło: <br/><input type="password" name="pass"/><br/>
                    <input type="submit" value="Zaloguj się"/>
                </form>
                <?php
                if (isset($_SESSION['e_logging']))
                {
                    echo '<div class="error">'.$_SESSION['e_logging'].'</div>';
                    unset($_SESSION['e_logging']);
                }
                ?>
            </div>
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
            <br>
            Wykonał Kamil Cinner
		</div>
    </footer>
</body>

</html>