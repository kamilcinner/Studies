//window.onload = clearCookies;
//setCookie('loaded_fibers',data, 1)
//getCookie('loaded_fibers');
//<script src="cookie.js"></script>

function clearCookies(){deleteCookie('loaded_fibers');}

function setCookie(cname, cvalue, exdays)
{
    var d = new Date();
    d.setTime(d.getTime() + (exdays * 24 * 60 * 60 * 1000));
    var expires = "expires="+d.toUTCString();
    document.cookie = cname + "=" + cvalue + ";" + expires + ";path=/";
}

function deleteCookie(cname)
{
    var d = new Date();
    d.setTime(d.getTime() - 1);
    var expires = "expires="+d.toUTCString();
    document.cookie = cname + "=;" + expires + ";path=/";
}
  
function getCookie(cname)
{
    var name = cname + "=";
    var ca = document.cookie.split(';');
    for(var i = 0; i < ca.length; i++)
    {
        var c = ca[i];
        while (c.charAt(0) == ' ')
        {
            c = c.substring(1);
        }
        if (c.indexOf(name) == 0)
        {
            return c.substring(name.length, c.length);
        }
    }
    return "";
}
  
function checkCookie()
{
    var user = getCookie("username");
    if (user != "")
    {
        alert("Welcome again " + user);
    }
    else
    {
        user = prompt("Please enter your name:", "");
        if (user != "" && user != null)
        {
            setCookie("username", user, 365);
        }
    }
}