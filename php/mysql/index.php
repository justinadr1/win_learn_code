<?php
$host = "localhost";
$user = "root";
$password = "";
$database = "learnweb";

$conn = new mysqli($host, $user, $password, $database);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$result = $conn->query("SHOW TABLES");

$selectedTable = $_GET['table'] ?? null;
?>
<!DOCTYPE html>
<html>
<head>
    <title>Database Tables</title>
    <style>
        table {
            border-collapse: collapse;
            width: 80%;
            margin-bottom: 20px;
        }
        th, td {
            border: 1px solid #333;
            padding: 8px;
        }
        th {
            background: #f0f0f0;
        }
        button {
            padding: 5px 10px;
            cursor: pointer;
        }
    </style>
</head>
<body>

<h1>Tables in Database: <?= htmlspecialchars($database) ?></h1>

<?php if ($result->num_rows > 0): ?>
<table>
    <tr>
        <th>Table Name</th>
        <th>Action</th>
    </tr>

    <?php while ($row = $result->fetch_array()): ?>
        <tr>
            <td><?= htmlspecialchars($row[0]) ?></td>
            <td>
                <form method="get" style="margin:0">
                    <input type="hidden" name="table" value="<?= htmlspecialchars($row[0]) ?>">
                    <button type="submit">View</button>
                </form>
            </td>
        </tr>
    <?php endwhile; ?>
</table>
<?php else: ?>
    <p>No tables found in this database.</p>
<?php endif; ?>

<?php
if ($selectedTable) {

    $tables = $conn->query("SHOW TABLES")->fetch_all(MYSQLI_NUM);
    $tableNames = array_column($tables, 0);

    if (in_array($selectedTable, $tableNames)) {

        echo "<h2>Table: " . htmlspecialchars($selectedTable) . "</h2>";

        $data = $conn->query("SELECT * FROM `$selectedTable`");

        if ($data && $data->num_rows > 0) {

            echo "<table><tr>";

            // Column headers
            while ($field = $data->fetch_field()) {
                echo "<th>" . htmlspecialchars($field->name) . "</th>";
            }
            echo "</tr>";

            // Rows
            while ($row = $data->fetch_assoc()) {
                echo "<tr>";
                foreach ($row as $cell) {
                    echo "<td>" . htmlspecialchars((string)$cell) . "</td>";
                }
                echo "</tr>";
            }

            echo "</table>";
        } else {
            echo "<p>No data in this table.</p>";
        }
    } else {
        echo "<p>Invalid table selected.</p>";
    }
}

$conn->close();
?>

</body>
</html>
