<?php session_start();
    $OK = true;
    if (isset($_POST['email'])) {
        //Bot or not? That's the question
        $secret = "6LcnKnMUAAAAAFgk6OLDar0b-ug07kGn21A2qdM8";
        $check = file_get_contents('https://www.google.com/recaptcha/api/siteverify?secret='.$secret.'&response='.$_POST['g-recaptcha-response']);
        $result = json_decode($check);
        if (!$result->success) {
            $_SESSION['err_bot'] = "Prove that you are not a bot!";
            //$OK = false;
            header('Location: index.php');
            exit();
        }

        $email = filter_input(INPUT_POST, 'email', FILTER_VALIDATE_EMAIL);
        $_SESSION['given_email'] = $_POST['email'];
        if (empty($email)) {
            
            $_SESSION['err_email'] = "It is not a valid email address!";
            $OK = false;
        } else {
            require_once 'database.php';
            //Do this email already exist in our database?
            $query = $db->prepare("SELECT id FROM users WHERE email='$email'");
            $query->execute();
            if ($query->rowCount() > 0) {
                $_SESSION['errE_email'] = "This email address already exist in our database!";
                $OK = false;
            } else {
                unset($_SESSION['given_email']);
                $query = $db->prepare('INSERT INTO users VALUES (NULL, :email)');
                $query->bindValue(':email', $email, PDO::PARAM_STR);
                $query->execute();
            }
        }
        if (!$OK) {
            header('Location: index.php');
            exit();
        }
    } else {
        header('Location: index.php');
        exit();
    }
?>
<!DOCTYPE html>
<html lang="pl">
<head>

    <meta charset="utf-8">
    <title>Zapisanie się do newslettera</title>
    <meta name="description" content="Używanie PDO - zapis do bazy MySQL">
    <meta name="keywords" content="php, kurs, PDO, połączenie, MySQL">

    <meta http-equiv="X-Ua-Compatible" content="IE=edge">

    <link rel="stylesheet" href="main.css">
    <link href="https://fonts.googleapis.com/css?family=Lobster|Open+Sans:400,700&amp;subset=latin-ext" rel="stylesheet">
    <!--[if lt IE 9]>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/html5shiv/3.7.3/html5shiv.min.js"></script>
    <![endif]-->

</head>

<body>

    <div class="container">

        <header>
            <h1>Newsletter</h1>
        </header>

        <main>
            <article>
                <p>Dziękujemy za zapisanie się na listę mailową naszego newslettera!</p>
            </article>
        </main>

    </div>

</body>
</html>