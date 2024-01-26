<?php
// python code to upload file
    // send_image = requests.post('http://eco-rover.vibd.me/upload.php', files={'image': open('test.jpg', 'rb')})

// now php code to receive image

// time zone set to Asia/Dhaka
date_default_timezone_set('Asia/Dhaka');

// get current time
$time = time();

if($_SERVER['REQUEST_METHOD'] == 'POST'){
    // get image
    $image = $_FILES['image']['tmp_name'];
    // get image name
    $image_name = $_FILES['image']['name'];
    // set image name to current time
    $image_name = $time . '.jpg';
    // save image to uploads folder
    move_uploaded_file($image, $image_name);
}

?>