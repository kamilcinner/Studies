function loadFiber(db_id){get_base_content(
    'fiberLoad.php',
    'id='+db_id,
    function(data)
    {
        $('#content').html(data);
    });
}