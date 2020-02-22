// scroll reset
jQuery(function($)
{
    $.scrollTo(0);
    $('.scrollup').click(function(){$.scrollTo($('body'), 1000);});
});

// show when scrolling
$(window).scroll(function(){
    if($(this).scrollTop()>300) $('.scrollup').fadeIn();
    else $('.scrollup').fadeOut();
});