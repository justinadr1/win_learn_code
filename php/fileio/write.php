<?php

$handle = fopen("log.txt", "a");
if ($handle) {
    echo "File opened successfully.\n";
} else {
    echo "Failed to open file.";
}

fwrite($handle, "\n[3] database learnweb added users table");

fclose($handle);