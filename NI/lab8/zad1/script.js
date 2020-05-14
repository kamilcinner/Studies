function pokaz(id)
{
    var tresc="";
    switch (id)
    { case 2: tresc += pokazGalerie();break;
        case 3: tresc += pokazPost(); break;
        case 4: tresc += pokazKontakt();break;
        default: tresc += pokazOmnie();
    }
    //pobierz element o wskazanym id i ustaw jego nową zawartość:
    document.getElementById('blok').innerHTML = tresc;
}
function pokazOmnie() {
    var tresc = '<h2><br />O mnie</h2> ';
    //operator += uzupełnia łańcuch kolejną porcją znaków:
    tresc += '<p>Lorem ipsum dolor pariatur,...</p>' +
        '<p class="srodek"><img src="images/original/baner.JPG" alt="Zdjęcie" /></p>' +
        '<article><h2>Moje hobby</h2><p>' +
        'Lorem ipsum dolor sit amet,...' +
        'mollit anim id est laborum.</p></article>';
    //przekaż wynik – gotową zawartość – do miejsca wywołania funkcji:
    return tresc;
}
function pokazGalerie()
{
    var tresc='<h2><br />Moja galeria</h2>';
    tresc+=' <div class="galeria">';
    //wygeneruj kod HTML z obrazami za pomocą pętli for:
    for (let i=1;i<=10;i++)
    {
        tresc+='<div class="slajd"><a href="images/obraz'+i+'.JPG" data-lightbox="galeria" data-title="Obraz '+i+'"><img src="images/min/obraz'+i+'.JPG" alt="Obraz"/></a></div>';
    }
    return tresc+'</div>';
}
function pokazKontakt()
{
    var tresc='<h2><br />Kontakt</h2>';
    //uzupełnij treść:
    // tresc+= ...
    return tresc;
}
function pokazPost()
{
    //funkcja generuje kod formularza – dane wpisane w odpowiednie pola przez
    //użytkownika zostaną przekazane mailem na wskazany adres, ale najpierw po
    //zajściu zdarzenia submit (wyślij) – zostanie wywołana funkcja pokazDane()
    tresc='<h2><br />Dodaj post</h2>';
    tresc+=
        '<article class="srodek" ><form method="post" onsubmit="return pokazDane();">'+
            'Twój email:<br /> <input type="email" name="email" id="email" required /><br />'+
            'Nazwisko i Imię:<br /> <input name="name" id="name" required /><br />'+
            'Telefon:<br /> <input type="number" name="phone" id="phone" required /><br />'+
            'Zainteresowania:<br />' +
                '<input type="checkbox" name="interest" value="Sport"/> Sport' +
                '<input type="checkbox" name="interest" value="Muzyka"/> Muzyka' +
                '<input type="checkbox" name="interest" value="Film"/> Film' +
                '<input type="checkbox" name="interest" value="Inne"/> Inne' +
            '<br />'+
            'Wiek:<br />' +
                '<input type="radio" name="age" value="Mniej niż 10"/> Mniej niż 10' +
                '<input type="radio" name="age" value="10-20"/> 10-20' +
                '<input type="radio" name="age" value="21-30"/> 21-30' +
                '<input type="radio" name="age" value="31-40"/> 31-40' +
                '<input type="radio" name="age" value="41-50"/> 41-50' +
                '<input type="radio" name="age" value="Więcej niż 50"/> Więcej niż 50' +
            '<br />'+
            'Komentarz: <br /><textarea rows="3" cols="20" id="wiadomosc" name="wiadomosc" required></textarea>'+
            '<br /> <input type="submit" name="wyslij" value="Wyślij" />'+
        '</form></article>';
    
    return tresc;
}
function pokazDane()
{
    //Funkcja zbiera dane wpisane w pola formularza i wyświetla okienko
    //typu confirm do zatwierdzenia przez użytkownika:
    let dane = "Następujące dane zostaną wysłane:\n";
    let interestObjects = document.getElementsByName('interest');
    let interests = '';
    for (let interest of interestObjects) {
        if (interest.checked) {
            interests += interest.value + ' ';
        }
    }

    let ageObjects = document.getElementsByName('age');
    let age;
    for (let ageRange of ageObjects) {
        if (ageRange.checked) {
            age = ageRange.value;
            break;
        }
    }

    dane+=
        'Email: ' + document.getElementById('email').value + '\n' +
        'Nazwisko i Imię: ' + document.getElementById('name').value + '\n' +
        'Telefon: ' + document.getElementById('phone').value + '\n' +
        'Zainteresowania: ' + interests + '\n' +
        'Wiek: ' + age + '\n' +
        'Komentarz: ' + document.getElementById('wiadomosc').value + '\n';

    return window.confirm(dane);
}
