window.onload = loadFibers;

var newHTML = "";
var fbn = 1;

function get_base_content(callback)
{
    var dataToSend = 'fiber_block_number=' + fbn;

    $.ajax({
        url: 'get_fibers_data_pack.php',
        type: 'POST',
        data: dataToSend,
        async: true,
        success: callback
    });
}

function loadFibers(callback){get_base_content(function(data)
{
    var loadedFibers = data;

    if (loadedFibers == "db_fibers_end")
    {
        $("#show_more").css('display', 'none');
        return;
    }

    newHTML += '<div id="fiber_block_' + fbn + '">' + loadedFibers + '</div>'

    document.getElementById('newest').innerHTML =
        newHTML +
        '<div onclick="loadFibers()" id="show_more">' +
            '<p>Pokaż kolejne</p>' +
        '</div>'
    ;

    $("#fiber_block_" + fbn + " .fiber").css('display', 'none');
    $("#fiber_block_" + fbn + " .fiber").fadeIn(2000);

    $("#show_more").fadeIn(1000);
    $("#show_more").css('display', 'inline-block');

    fbn++;
})}