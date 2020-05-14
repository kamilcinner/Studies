function slideSwitch() {
    let $active = $('#slideshow IMG.active');
    if ($active.length === 0)
        $active = $('#slideshow IMG:last');
    const $next = $active.next().length ? $active.next()
        : $('#slideshow IMG:first');
    $active.addClass('last-active');
    $next.css({opacity: 0.0})
        .addClass('active')
        .animate({opacity: 1.0}, 1000, function () {
            $active.removeClass('active last-active');
        });
}
$(function () {
    setInterval("slideSwitch()", 3000);
});
