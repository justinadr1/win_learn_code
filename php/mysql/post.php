<?php
$host = "localhost";
$user = "root";
$password = "";
$database = "learnweb";

$conn = new mysqli($host, $user, $password, $database);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$table = $_GET['table'] ?? null;

if (!$table) {
    die("No table selected.");
}

$columns = $conn->query("SHOW COLUMNS FROM `$table`")->fetch_all(MYSQLI_ASSOC);

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $fields = [];
    $values = [];
    foreach ($columns as $col) {
        $colName = $col['Field'];
        if (isset($_POST[$colName])) {
            $fields[] = "`$colName`";
            $values[] = "'" . $conn->real_escape_string($_POST[$colName]) . "'";
        }
    }
    $sql = "INSERT INTO `$table` (" . implode(",", $fields) . ") VALUES (" . implode(",", $values) . ")";
    if ($conn->query($sql)) {
        echo "<p>Row added successfully!</p>";
    } else {
        echo "<p>Error: " . $conn->error . "</p>";
    }
}
?>

<h1>Add Row to <?= htmlspecialchars($table) ?></h1>
<form method="post">
<?php foreach ($columns as $col): ?>
    <label><?= htmlspecialchars($col['Field']) ?>:</label>
    <input type="text" name="<?= htmlspecialchars($col['Field']) ?>"><br>
<?php endforeach; ?>
<button type="submit">Add Row</button>
</form>
