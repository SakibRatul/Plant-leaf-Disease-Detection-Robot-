<?php
// show all images in the directory
$images = glob("*.jpg");
foreach($images as $image) {
    echo '<img src="' . $image . '" /><br />';
}
?>