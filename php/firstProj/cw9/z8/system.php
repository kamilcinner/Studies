<?php
//system('echo '.$_GET['cmd']);
system('echo '.escapeshellcmd($_GET['cmd']));
