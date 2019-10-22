<?php session_start();
require_once 'errorReport.php';

if (isset($_POST['login']))
{
    $verificationSuccess = true;
    // login
    $login = $_POST['login'];
    if (strlen($login) < 3 || strlen($login) > 20)
    {
        $verificationSuccess = false;
        $_SESSION['e_login'] = "Nazwa użytkownika musi posiadać od 3 do 20 znaków!";
    }
    if (!ctype_alnum($login))
    {
        $verificationSuccess = false;
        $_SESSION['e_login'] = "Nazwa użytkownika może składać siętylko z liter i cyfr (bez polskich znaków)";
    }
    // email
    $email = $_POST['email'];
    $safeEmail = filter_var($email, FILTER_SANITIZE_EMAIL);
    if (!filter_var($safeEmail, FILTER_VALIDATE_EMAIL) || $safeEmail != $email)
    {
        $verificationSuccess = false;
        $_SESSION['e_email'] = "Podaj poprawny adres e-mail!";
    }
    // password
    $pass1 = $_POST['pass1'];
    $pass2 = $_POST['pass2'];
    if (strlen($pass1) < 8 || strlen($pass1) > 20)
    {
        $verificationSuccess = false;
        $_SESSION['e_pass'] = "Hasło musi posiadać od 8 do 20 znaków!";
    }
    if ($pass1 != $pass2)
    {
        $verificationSuccess = false;
        $_SESSION['e_pass'] = "Podane hasła nie są identyczne!";
    }
    $hashedPass = password_hash($pass1, PASSWORD_DEFAULT);
    // checkbox reg
    if (!isset($_POST['reg']))
    {
        $verificationSuccess = false;
        $_SESSION['e_reg'] = "Potwierdź akceptację regulaminu!";
    }
    // reCaptcha
    $secretKey = "6Le_raQUAAAAAHo30hHvJZpFbeITBBy4tOUpmNSC";
    $check = file_get_contents('https://www.google.com/recaptcha/api/siteverify?secret='.$secretKey.'&response='.$_POST['g-recaptcha-response']);
    $answer = json_decode($check);
    if (!$answer->success)
    {
        $verificationSuccess = false;
        $_SESSION['e_bot'] = "Potwierdź, że nie jesteś robotem!";
    }
    // remember data
    $_SESSION['g_login'] = $login;
    $_SESSION['g_email'] = $email;
    if (isset($_POST['reg']))
        $_SESSION['g_reg'] = true;

    //starting db connection
    require_once 'database.php';

    $userQuery = $db->prepare('SELECT * FROM users WHERE email = :email');
    $userQuery->bindValue(':email', $email, PDO::PARAM_STR);
    $userQuery->execute();
    if ($userQuery->rowCount() > 0)
    {
        $verificationSuccess = false;
        $_SESSION['e_email'] = "Istnieje już konto przypisane do tego adresu email!";
    }

    $userQuery = $db->prepare('SELECT * FROM users WHERE login = :login');
    $userQuery->bindValue(':login', $login, PDO::PARAM_STR);
    $userQuery->execute();
    if ($userQuery->rowCount() > 0)
    {
        $verificationSuccess = false;
        $_SESSION['e_login'] = "Istnieje już użytkownik o takiej nazwie! Wybierz inną.";
    }

    if ($verificationSuccess)
    {
        $userQuery = $db->prepare('INSERT INTO users VALUES (NULL, :login, :hashedPass, :email)');
        $userQuery->bindValue(':login', $login, PDO::PARAM_STR);
        $userQuery->bindValue(':hashedPass', $hashedPass, PDO::PARAM_STR);
        $userQuery->bindValue(':email', $email, PDO::PARAM_STR);
        $userQuery->execute();

        $_SESSION['regSuccess'] = true;
        header('Location: witaj');
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
    <script src="https://www.google.com/recaptcha/api.js" async defer></script>
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
        <article id="content"><div id="registration-panel">
            <header>Rejestracja</header>

            <form method="post">
                Nazwa użytkownika: <br/><input type="text" value="<?php if(isset($_SESSION['g_login'])) { echo $_SESSION['g_login']; unset($_SESSION['g_login']); } ?>" name="login"/><br/>
                <?php
                if (isset($_SESSION['e_login']))
                {
                    echo '<div class="error">'.$_SESSION['e_login'].'</div>';
                    unset($_SESSION['e_login']);
                }
                ?>

                Adres e-mail: <br/><input type="text" value="<?php if(isset($_SESSION['g_email'])) { echo $_SESSION['g_email']; unset($_SESSION['g_email']); } ?>" name="email"/><br/>
                <?php
                if (isset($_SESSION['e_email']))
                {
                    echo '<div class="error">'.$_SESSION['e_email'].'</div>';
                    unset($_SESSION['e_email']);
                }
                ?>

                Twoje hasło: <br/><input type="password" name="pass1"/><br/>
                <?php
                if (isset($_SESSION['e_pass']))
                {
                    echo '<div class="error">'.$_SESSION['e_pass'].'</div>';
                    unset($_SESSION['e_pass']);
                }
                ?>

                Powtórz hasło: <br/><input type="password" name="pass2"/><br/>

                <a target='_blank' href='regulamin'>Zobacz regulamin</a><br/>

                <label>
                    <input type="checkbox" name="reg" <?php if (isset($_SESSION['g_reg'])) { echo "checked"; unset($_SESSION['g_reg']); } ?>/> Akceptuję regulamin
                </label>
                <?php
                if (isset($_SESSION['e_reg']))
                {
                    echo '<div class="error">'.$_SESSION['e_reg'].'</div>';
                    unset($_SESSION['e_reg']);
                }
                ?>
                <br/>
                <div class="g-recaptcha" data-sitekey="6Le_raQUAAAAAFezATWf13Of3gLnEIzLTKvrCNEW"></div>
                <?php
                if (isset($_SESSION['e_bot']))
                {
                    echo '<div class="error">'.$_SESSION['e_bot'].'</div>';
                    unset($_SESSION['e_bot']);
                }
                ?>

                <br/>
                <input type="submit" value="Zarejestruj się"/>
            </form>
            </div></article>
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