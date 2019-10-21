//randomizing 12 numbers
var number;
var numbers = new Array(12);
for (i = 0;i < 12;i++) {
    number = Math.floor(Math.random() * 12);
    numbers[i] = number;
    for (j = 0;j < i;j++) {
        if (number == numbers[j]) {
            i--; break;
        }
    }
}
//randomizing 12 cards
var cardsList = ["ciri.png", "geralt.png", "jaskier.png", "jaskier.png", "iorweth.png", "triss.png", "geralt.png", "yen.png", "ciri.png", "triss.png", "yen.png", "iorweth.png"];
var cards = new Array(12);
for (i = 0;i < 12;i++) {
    cards[i] = cardsList[numbers[i]];
}
//audio play
var questUpdate = new Audio("audio/questUpdate.wav");
var questComplete = new Audio("audio/questComplete.wav");

var songsList = ["audio/1.mp3", "audio/2.mp3", "audio/3.mp3", "audio/4.mp3"]
var songNr;
var songNrOld = 4;
var song;

//window.onload = playSongs;

for (i = 0;i < 12;i++) {
    var c$i = document.getElementById('c' + i);
    //c$i.addEventListener("click", function() {revealCard(i);});
    //document.getElementById('c' + i).addEventListener("click", function() {revealCard(i);});
}

//fix this :)
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
//ende

var oneVisible = false;
var turnCounter = 0;
var visibleCardNumber;
var lock = false;
var pairsLeft = 6;
var start = true;

function revealCard(cardNumber) {
    if (start == true) {
        playSongs();
        start = false;
    }

    var cardOpacityValue = $('#c' + cardNumber).css('opacity');
    if (cardOpacityValue != 0 && lock == false) {
        lock = true;
        var image = "url(img/" + cards[cardNumber] + ")";
        $('#c' + cardNumber).css('background-image', image);
        $('#c' + cardNumber).addClass('cardActive');
        $('#c' + cardNumber).removeClass('card');

        if (oneVisible == false) {
            oneVisible = true;
            visibleCardNumber = cardNumber;
            lock = false;
        } else {
            if (cards[visibleCardNumber] == cards[cardNumber] && visibleCardNumber != cardNumber) {
                if (pairsLeft != 1) playQuestUpdate();
                setTimeout(function() {hide2Cards(cardNumber, visibleCardNumber)}, 500); //750
            } else {
                setTimeout(function() {restore2Cards(cardNumber, visibleCardNumber)}, 700); //1000
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
        playQuestComplete();
        $('.board').html('<h1><br/>You win!<br/>Done in ' + turnCounter + ' turns</h1><br/><br/><span id = "restart" onclick = "location.reload()">Start over</span>');
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
function playQuestUpdate() {
    questUpdate.load();
    questUpdate.play();
}
function playQuestComplete() {
    questComplete.play();
}
function playSongs() {
    songNr = Math.floor(Math.random() * 4);
    if (songNr != songNrOld) {
        song = new Audio(songsList[songNr]);
        song.play();
        song.onended = function() {playSongs();};
    } else playSongs();
}