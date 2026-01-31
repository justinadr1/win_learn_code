<?php
$imagesPerPage = 3;
$allImages = array_filter(scandir(__DIR__ . "/uploads"), function($file) {
    return preg_match("/\.(jpg|jpeg|png|gif)$/i", $file);
});
$totalImages = count($allImages);
$totalPages = ceil($totalImages / $imagesPerPage);

$page = isset($_GET['page']) ? max(1, intval($_GET['page'])) : 1;
$start = ($page - 1) * $imagesPerPage;
$images = array_slice($allImages, $start, $imagesPerPage);
?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Image Gallery</title>
        <style>
            body { font-family: Arial; padding: 20px; }
            img { width: 150px; height: 150px; object-fit: cover; margin: 5px; border: 1px solid #ccc; }
        </style>
    </head>
    <body>
        <h1>Image Gallery</h1>
    
        <div class="gallery">
        <?php foreach($images as $img): ?>
            <img src="uploads/<?php echo $img ?>" alt="">
        <?php endforeach; ?>
        </div>

        <div id="pagination">
        <?php for($i=1; $i<=$totalPages; $i++): ?>
            <a href="?page=<?php echo $i ?>" style="margin:2px; <?php if($i==$page) echo 'font-weight:bold;' ?>"><?php echo $i ?></a>
        <?php endfor; ?>
        </div>

        <p><a href="upload.php">Upload More Images</a></p>
    </body>
</html>
