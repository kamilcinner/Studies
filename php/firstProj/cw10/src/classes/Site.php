<?php

class Site {
    protected string $content;
    protected string $title = 'Modułowy serwis PHP';
    protected string $keywords = 'narzędzia internetowe, php, formularz, galeria';
    protected array $buttons = [
        'Kontakt' => '?site=index',
        'Galeria' => '?site=gallery',
        'Formularz' => '?site=form',
        'O nas' => '?site=about'
    ];

    public function setContent(string $content): void {
        $this->content = $content;
    }

    function setTitle(string $title): void {
        $this->title = $title;
    }

    public function setKeywords(string $keywords): void {
        $this->keywords = $keywords;
    }

    public function setButtons(array $buttons): void {
        $this->buttons = $buttons;
    }

    public function show(): void {
        $this->showHeader();
        $this->showContent();
        $this->showFooter();
    }

    public function showHeader(): void {
        ?>
        <!DOCTYPE html>
        <html>
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <?php
        $this->setStyles('assets/css/style.css');
        echo "<title>" . $this->title . "</title></head><body>";
    }

    public function setStyles(string $url): void {
        echo '<link rel="stylesheet" href="' . $url . '" type="text/css" />';
    }

    public function showContent(): void {
        echo "<div id='tresc'>";
        echo "<div id='nag'>";
        echo "<img src='/cw10/assets/images/photo.jpg' alt='photo' /></div>";
        echo "<div id='menu'>";
        $this->showMenu();
        echo "</div>";
        echo "<h1>" . $this->title . "</h1>";
        echo $this->content . "</div>";
    }

    public function showMenu(): void {
        echo "<div id='nav'>";
        foreach ($this->buttons as $name => $url) {
            echo ' <a href="' . $url . '">' . $name . '</a>';
        }
        echo "</div>";
    }

    public function showFooter(): void {
        echo '<div id="footer"> &copy; KC </div>';
        echo '</body></html>';
    }

    public function showTitle(): void {
        echo "<title>$this->title</title>";
    }

    public function showKeywords(): void {
        echo '<meta name="keywords" contents="$this->keywords">';
    }
}
