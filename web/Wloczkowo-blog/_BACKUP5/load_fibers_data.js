window.onload = loadFibers;

var newHTML = "";
var fbn = 1;
var first_call = true;

function get_base_content(_url, dataToSend, callback)
{
    $.ajax({
        url: _url,
        type: 'POST',
        data: dataToSend,
        async: true,
        success: callback
    });
}

function loadFibers(){get_base_content(
    'get_fibers_data_pack.php',
    'fiber_block_number=' + fbn, 
    function(data)
    {
        if (first_call)
        {
            $('#content').html('<div id="fibers"></div>');
            first_call = false;
        }

        var loadedFibers = data;

        if (loadedFibers == "db_fibers_end")
        {
            $("#show_more").fadeOut(1000);
            return;
        }

        newHTML += '<div id="fiber_block_' + fbn + '">' + loadedFibers + '</div>';

        document.getElementById('fibers').innerHTML =
            newHTML +
            '<div onclick="loadFibers()" id="show_more">' +
                '<p>Pokaż kolejne</p>' +
            '</div>'
        ;

        $("#fiber_block_" + fbn + " .fiber").css('display', 'none');
        $("#fiber_block_" + fbn + " .fiber").fadeIn(1000);

        $("#show_more").fadeIn(1000);
        $("#show_more").css('display', 'inline-block');

        fbn++;
    });
}

function viewFiber(db_id){get_base_content(
    'getFiberById.php',
    'id='+db_id,
    function(data)
    {
        $('#content').html(data);
    });
    first_call = true;
    newHTML = "";
    fbn = 1;
}