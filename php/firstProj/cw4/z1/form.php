<?php
include_once 'utils.php';
printForm();

$action = filter_input(INPUT_POST, 'submit');
switch ($action) {
    case "Dodaj": add(); break;
    case "Pokaz": show(); break;
    case "Java": showOrder("Java"); break;
    case "PHP": showOrder("PHP"); break;
    case "C++": showOrder("C++"); break;
    default: {}
}

function printForm() {?>
    <!DOCTYPE html>
    <html lang="pl">
    <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Formularze</title>

    <link rel="stylesheet" href="css/forms.css" type="text/css">
    </head>

    <body>
    <div id="container">
        <div id="banner"><h1>Szybki kurs HTML</h1></div>
        <div id="menu">
        <a href="">Podstawowe znaczniki</a>
        <a href="">Tworzenie tabel</a>
        <a href="">Budowa formularzy</a>
        </div>
        <div id="content">
        <h2>Podstawowe znaczniki HTML to:</h2>
        <ul>
            <li>&lt;form&gt; - znacznik podstawowy zawierający pola formularza</li>
            <li>&lt;input&gt; - znacznik umożliwiający wstawienie różnych pól (pole tekstowe, przycisku typu radio, przycisk typu checkbox) w zależności od wartości jego atrybutu type</li>
            <li>&lt;select&gt; - pole formularza typu lista rozwijana</li>
            <li>&lt;textarea&gt; - pole formularza typu obszar tekstowy</li>
            <li>&lt;button&gt; - pole formularza typu przycisk</li>
        </ul>
        <h2>Przykładowy formularz</h2>
        <form action="form.php" method="post">
            <table>
            <tr>
                <td><label for="id_lastname">Nazwisko:</label></td>
                <td><input type="text" id="id_lastname" name="lastname" value="Testsurname"></td>
            </tr>
            <tr>
                <td><label for="id_age">Wiek:</label></td>
                <td><input type="number" id="id_age" name="age" value="12"></td>
            </tr>
            <tr>
                <td><label for="id_country">Państwo:</label></td>
                <td>
                <select id="id_country" name="country">
                    <option value="pl">Polska</option>
                </select>
                </td>
            </tr>
            <tr>
                <td><label for="id_email">Adres email:</label></td>
                <td><input type="email" id="id_email" name="email" value="test@email.example"></td>
            </tr>
            </table>
            <h3>Zamawiam tutorial z języka:</h3>
            <?php
            $tech = ["C", "C++", "Java", "C#", "Html", "CSS", "XML", "PHP", "JavaScript"];

            foreach ($tech as $item) {
                echo "<input type='checkbox' id='id_$item' name='tech[]' value='$item'><label for='id_$item'>$item</label>";
            }
            ?>
            <h3>Sposób zapłaty:</h3>
            <input type="radio" id="id_ec" name="payment" value="ec"><label for="id_ec">eurocard</label>
            <input type="radio" id="id_vs" name="payment" value="vs"><label for="id_vs">visa</label>
            <input type="radio" id="id_pb" name="payment" checked value="pb"><label for="id_pb">przelew bankowy</label><br>
            <input type="submit" name="submit" value="Wyślij">
            <input type="reset" value="Wyczyść">
            <input type="submit" name="submit" value="Dodaj">
            <input type="submit" name="submit" value="Pokaz">
            <input type="submit" name="submit" value="Java">
            <input type="submit" name="submit" value="PHP">
            <input type="submit" name="submit" value="C++">
        </form>
        </div>
        <div id="footer">&copy;KC</div>
    </div>
    </body>
    </html>
<?php }
// printServerArray();
?>