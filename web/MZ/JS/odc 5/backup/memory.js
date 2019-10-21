var cards = ["ciri.png", "geralt.png", "jaskier.png", "jaskier.png", "iorweth.png", "triss.png", "geralt.png", "yen.png", "ciri.png", "triss.png", "yen.png", "iorweth.png"];

//alert(cards[4]);
//console.log(cards);

var c0 = document.getElementById('c0');
var c1 = document.getElementById('c1');
var c2 = document.getElementById('c2');
var c3 = document.getElementById('c3');

var c4 = document.getElementById('c4');
var c5 = document.getElementById('c5');
var c6 = document.getElementById('c6');
var c7 = document.getElementById('c7');

var c8 = document.getElementById('c8');
var c9 = document.getElementById('c9');
var c10 = document.getElementById('c10');
var c11 = document.getElementById('c11');

c0.addEventListener("click", function() {revealCard(0);});
c1.addEventListener("click", function() {revealCard(1);});
c2.addEventListener("click", function() {revealCard(2);});
c3.addEventListener("click", function() {revealCard(3);});

c4.addEventListener("click", function() {revealCard(4);});
c5.addEventListener("click", function() {revealCard(5);});
c6.addEventListener("click", function() {revealCard(6);});
c7.addEventListener("click", function() {revealCard(7);});

c8.addEventListener("click", function() {revealCard(8);});
c9.addEventListener("click", function() {revealCard(9);});
c10.addEventListener("click", function() {revealCard(10);});
c11.addEventListener("click", function() {revealCard(11);});

var oneVisible = false;
var turnCounter = 0;
var visibleCardNumber;
var lock = false;
var pairsLeft = 6;

function revealCard(cardNumber) {
    var cardOpacityValue = $('#c' + cardNumber).css('opacity');
    //alert('Opacity: ' + cardOpacityValue);

    if (cardOpacityValue != 0 && lock == false) {
        lock = true;
        //alert(cardNumber);
        var image = "url(img/" + cards[cardNumber] + ")";
        $('#c' + cardNumber).css('background-image', image);
        $('#c' + cardNumber).addClass('cardActive');
        $('#c' + cardNumber).removeClass('card');

        if (oneVisible == false) {
            //first card
            oneVisible = true;
            visibleCardNumber = cardNumber;
            lock = false;
        } else {
            //second card
            if (cards[visibleCardNumber] == cards[cardNumber]) {
                //alert("para");
                setTimeout(function() {hide2Cards(cardNumber, visibleCardNumber)}, 750);
                
            } else {
                //alert("pudło");
                setTimeout(function() {restore2Cards(cardNumber, visibleCardNumber)}, 1000);
            }
            turnCounter++;
            $('.score').html("Turn counter: " + turnCounter);
            oneVisible = false;
        }
    }

    
}
function hide2Cards(nr1, nr2) {
    $('#c' + nr1).css('opacity', '0');
    $('#c' + nr2).css('opacity', '0');

    pairsLeft--;
    if (pairsLeft == 0) {
        $('.board').html('<h1><br/><br/>You win!<br/>Done in ' + turnCounter + ' turns</h1>');
    }
    lock = false;
}
function restore2Cards(nr1, nr2) {
    $('#c' + nr1).css('background-image', 'url(img/karta.png)');
    $('#c' + nr1).addClass('card');
    $('#c' + nr1).removeClass('cardActive');

    $('#c' + nr2).css('background-image', 'url(img/karta.png)');
    $('#c' + nr2).addClass('card');
    $('#c' + nr2).removeClass('cardActive');

    lock = false;
}