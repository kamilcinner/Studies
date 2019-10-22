window.onload = loadFibers;

var newHTML = "";
var fbn = 1;
var first_call = true;

var show_moreHTML =
    '<div onclick="loadFibers()" id="show_more">' +
        '<p>Pokaż kolejne</p>' +
    '</div>'
; 

function loadFibers(){getBaseContent(
    'workLoad.php',
    'fiber_block_number=' + fbn, 
    function(data)
    {
        if (first_call)
        {
            $('#content').html('<div id="fibers"></div>');
            first_call = false;
        }

        if (data == "db_fibers_end")
        {
            $("#show_more").fadeOut(500);
            return;
        }

        newHTML += '<div id="fiber_block_' + fbn + '">' + data + '</div>';

        document.getElementById('fibers').innerHTML = newHTML + show_moreHTML;

        $("#fiber_block_" + fbn + " .fiber").css('display', 'none');
        $("#fiber_block_" + fbn + " .fiber").fadeIn(500);

        $("#show_more").fadeIn(500);
        $("#show_more").css('display', 'inline-block');

        fbn++;
    });
}