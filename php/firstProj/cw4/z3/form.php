<?php
include_once 'tools.php';
printForm();

function printForm() {?>
    <!DOCTYPE html>
    <html lang="pl">
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <title>Ankieta</title>
    </head>

    <body>
        <h1>Wybierz technologie, które znasz:</h1>
        <form action="form.php" method="post">
            <?php
            global $schema;

            foreach ($schema as $item) {
                echo "<input type='checkbox' id='id_$item' name='tech[]' value='$item'><label for='id_$item'>$item</label><br>";
            }
            ?>
            <input type="submit" name="submit" value="Wyślij">
        </form>
    </body>
    </html>
<?php }
?>
