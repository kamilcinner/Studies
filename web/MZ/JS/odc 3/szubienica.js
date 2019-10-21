var haslo = "";
var haslo1 = "";
var dlugosc = 0;
var ileSkuch = 0;

var yes = new Audio("yes.wav");
var no = new Audio("no.wav");

window.onload = letsBegin;

function letsBegin() {
    document.getElementById("plansza").innerHTML =
    '<div id="container">' +
    "<form>" +
			'<input type="text" id="pole" placeholder="Podaj hasło" onfocus="this.placeholder=\'\'" onblur="this.placeholder=\'Podaj hasło\'">' +
			'<input type="submit" value="Zacznij grę" onclick="start()">' +
    "</form>" +
    "</div>";
}
function loadPas() {
    haslo = document.getElementById("pole").value;
    haslo = haslo.toUpperCase();
    dlugosc = haslo.length;

    for(i = 0;i < dlugosc;i++) {
        if (haslo.charAt(i) == " ") haslo1 = haslo1 + " ";
        else haslo1 = haslo1 + "-";
    }
}
function wypiszHaslo() {
    document.getElementById("plansza").innerHTML = haslo1;
}

var litery = new Array(36);
litery[0] = "A"; litery[1] = "Ą"; litery[2] = "B";
litery[3] = "C"; litery[4] = "Ć"; litery[5] = "D";
litery[6] = "E"; litery[7] = "Ę"; litery[8] = "F";
litery[9] = "G"; litery[10] = "H"; litery[11] = "I";
litery[12] = "J"; litery[13] = "K"; litery[14] = "L";
litery[15] = "Ł"; litery[16] = "M"; litery[17] = "N";
litery[18] = "Ń"; litery[19] = "O"; litery[20] = "Ó";
litery[21] = "P"; litery[22] = "Q"; litery[23] = "R";
litery[24] = "S"; litery[25] = "Ś"; litery[26] = "T";
litery[27] = "U"; litery[28] = "V"; litery[29] = "W";
litery[30] = "X"; litery[31] = "Y"; litery[32] = "Z";
litery[33] = "Ż"; litery[34] = "Ź";

function start() {
    loadPas();
    document.getElementById("szubienica").innerHTML = '<img src="img/s0.jpg" alt=""/>';
    var trescDiva = "";
    for(i = 0;i < 35;i++) {
        var element = "lit" + i;
        trescDiva = trescDiva + '<div class="litera" onclick="sprawdz(' + i + ')" id="' + element + '">' + litery[i] + '</div>';
        if ((i + 1) % 7 == 0) trescDiva = trescDiva + '<div style="clear: both;"></div>';
    }
    document.getElementById("alfabet").innerHTML = trescDiva;

    wypiszHaslo();
}

String.prototype.ustawZnak = function(miejsce, znak) {
    if (miejsce > this.length - 1) return this.toString();
    else return this.substr(0, miejsce) + znak + this.substr(miejsce + 1);
}

function sprawdz(nr) {
    var trafiona = false;
    for(i = 0;i < dlugosc;i++) {
        if (haslo.charAt(i) == litery[nr]) {
            haslo1 = haslo1.ustawZnak(i, litery[nr]);
            trafiona = true;
        }
    }
    var element = "lit" + nr;
    if (trafiona == true) {
        yes.play();
        document.getElementById(element).style.background = "#003300";
        document.getElementById(element).style.color = "#00C000";
        document.getElementById(element).style.border = "3px solid #00C000";
        document.getElementById(element).style.cursor = "default";
        wypiszHaslo();
    } else {
        no.play();
        document.getElementById(element).style.background = "#330000";
        document.getElementById(element).style.color = "#C00000";
        document.getElementById(element).style.border = "3px solid #C00000";
        document.getElementById(element).style.cursor = "default";
        document.getElementById(element).setAttribute("onclick", ";");
        //skucha
        ileSkuch++;
        var obraz = "img/s" + ileSkuch + ".jpg";
        document.getElementById("szubienica").innerHTML = '<img src="' + obraz + '" alt=""/>';
    }
    //wygrana
    if (haslo == haslo1) {
        document.getElementById("alfabet").innerHTML = "Tak jest! Podano prawidłowe hasło: " + haslo + '<br/><br/><span class=reset onclick="location.reload();">JESZCZE RAZ?</span>';
    }
    //przegrana
    if (ileSkuch >= 9) {
        document.getElementById("alfabet").innerHTML = "Przegrana! Prawidłowe hasło: " + haslo + '<br/><br/><span class=reset onclick="location.reload()">JESZCZE RAZ?</span>';
    }
}