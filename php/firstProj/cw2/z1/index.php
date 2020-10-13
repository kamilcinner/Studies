<div>
    <?php
    function printFormInput($name, $translation) {
        if (isset($_REQUEST[$name]) && ($_REQUEST[$name] !== "")) {
            $value = $_REQUEST[$name];
            if (is_array($value)) {
                echo "$translation: ";
                foreach ($value as $item) {
                    echo "$item ";
                }
                echo "<br>";
            }
            else {
                $value = htmlspecialchars(trim($_REQUEST[$name]));
                echo "$translation: $value<br>";
            }
        }
        else echo "$translation was empty.<br>";
    }

    echo '<h2>Form data:</h2>';

    $namesWithTranslations = [
        ['lastname', 'Nazwisko'],
        ['age', 'Wiek'],
        ['country', 'Państwo'],
        ['email', 'Adres email'],
        ['tech', 'Technologie'],
        ['payment', 'Sposób zapłaty']
    ];

    foreach ($namesWithTranslations as $item) {
        printFormInput($item[0], $item[1]);
    }
    ?>
</div>