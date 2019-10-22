function loadFiber(db_id){getBaseContent(
    'fiberLoad.php',
    'id='+db_id,
    function(data)
    {
        $('#content').html(data);
    });
}