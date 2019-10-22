$(document).ready(function() {

    var number1 = Math.round(Math.random() * 6) + 1;
    var number2 = Math.round(Math.random() * 6) + 1;
    var randomAnswer = number1 + number2;
    
    $.ajax({
       url: "index.php",
       method: "POST",
       dataType: "json",
       data: {randomAnswer: randomAnswer},
       success: function (result) {
          alert("result: " + result);
          $("#random").html(result);
       }
     });
    
    });