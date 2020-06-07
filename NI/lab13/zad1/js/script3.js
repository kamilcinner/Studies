// fetch
function getData(nazwaPliku) {
    const url = "http://localhost:63342/lab13/zad1/data/" + nazwaPliku + ".txt";

    fetch(url).then(response => {
        console.log(response.text().then(
            data => $("#s1").html(data))
        )
    });
}
