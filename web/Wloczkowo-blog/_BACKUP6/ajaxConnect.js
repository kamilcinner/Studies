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