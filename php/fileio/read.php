<?php

$handle = fopen("log.txt", "r");
if ($handle) {
    echo "File opened successfully.\n";
} else {
    echo "Failed to open file.";
}

$content = fread($handle, 100);

echo $content;

fclose($handle);