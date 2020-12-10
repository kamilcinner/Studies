<?php

function getForm(): string {
    $form = '';
    $form .= '<form action="?site=form" method="post">';
        $form .= '<table>';
            $form .= '<tr>';
                $form .= '<td><label for="id_lastname">Nazwisko:</label></td>';
                $form .= '<td><input type="text" id="id_lastname" name="lastname" value="Testsurname"></td>';
            $form .= '</tr>';
            $form .= '<tr>';
                $form .= '<td><label for="id_age">Wiek:</label></td>';
                $form .= '<td><input type="number" id="id_age" name="age" value="12"></td>';
            $form .= '</tr>';
            $form .= '<tr>';
                $form .= '<td><label for="id_country">Państwo:</label></td>';
                $form .= '<td>';
                    $form .= '<select id="id_country" name="country">';

                        $countries = ['Polska', 'Niemcy', 'Wielka Brytania', 'Czechy'];
                        foreach ($countries as $country) {
                            $form .= "<option value='$country'>$country</option>";
                        }

                    $form .= '</select>';
                $form .= '</td>';
            $form .= '</tr>';
            $form .= '<tr>';
                $form .= '<td><label for="id_email">Adres email:</label></td>';
                $form .= '<td><input type="email" id="id_email" name="email" value="test@email.example"></td>';
            $form .= '</tr>';
        $form .= '</table>';
        $form .= '<h3>Zamawiam tutorial z języka:</h3>';

        $tech = ["Java", "PHP", "CPP"];
        foreach ($tech as $item) {
            $form .= "<input type='checkbox' id='id_$item' name='tech[]' value='$item'><label for='id_$item'>$item</label>";
        }

        $form .= '<h3>Sposób zapłaty:</h3>';
        $form .= '<input type="radio" id="id_ec" name="payment" value="Master Card"><label for="id_ec">Master Card</label>';
        $form .= '<input type="radio" id="id_vs" name="payment" value="Visa"><label for="id_vs">Visa</label>';
        $form .= '<input type="radio" id="id_pb" name="payment" checked value="Przelew"><label for="id_pb">przelew bankowy</label><br>';
        $form .= '<input type="reset" value="Wyczyść">';
        $form .= '<input type="submit" name="submit" value="Dodaj">';
        $form .= '<input type="submit" name="submit" value="Pokaz">';
        $form .= '<input type="submit" name="submit" value="Java">';
        $form .= '<input type="submit" name="submit" value="PHP">';
        $form .= '<input type="submit" name="submit" value="CPP">';
        $form .= '<input type="submit" name="submit" value="Statystyki">';
        $form .= '<input type="submit" name="submit" value="Delete">';
    $form .= '</form>';
    return $form;
}
