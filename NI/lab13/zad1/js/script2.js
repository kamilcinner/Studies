// ajax
function getData(nazwaPliku) {
    const url = "http://localhost:63342/lab13/zad1/data/" + nazwaPliku + ".txt";

    $.ajax({url: url, success: function(result){
            $("#s1").html(result);
    }});
}
