<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    foreach ($_FILES['images']['tmp_name'] as $key => $tmp_name) {
        $filename = basename($_FILES['images']['name'][$key]);
        $target = __DIR__ . "/uploads/" . time() . "_" . $filename;
        move_uploaded_file($tmp_name, $target);
    }
    header("Location: upload.php?success=1");
    exit;
}
?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Upload Images</title>
    </head>
    <body>
        <h1>Upload Images</h1>
        <?php if(isset($_GET['success'])) echo "<p style='color:green'>Upload successful!</p>"; ?>
        <form action="" method="POST" enctype="multipart/form-data">
            <input type="file" name="images[]" multiple accept="image/*">
            <button type="submit">Upload</button>
        </form>
        <p><a href="index.php">Go to Gallery</a></p>
    </body>
</html>
