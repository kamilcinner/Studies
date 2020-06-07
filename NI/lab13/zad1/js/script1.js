//utworzenie obiektu xhr:
const xhr = new XMLHttpRequest();
function getData(nazwaPliku) {
    if (xhr) {
        var url = "http://localhost:63342/lab13/zad1/data/" + nazwaPliku + ".txt";
        xhr.open("GET", url);
        xhr.addEventListener("readystatechange", function () {
            if (xhr.readyState === 4) {
                document.getElementById("s1").innerHTML = xhr.responseText;
            }
        });
        xhr.send(null);
    }
}
