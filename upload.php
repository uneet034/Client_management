<?php
if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $targetDirectory = "uploads/";  // Directory to store uploaded files
    $targetFile = $targetDirectory . basename($_FILES["fileToUpload"]["name"]);
    $uploadOk = 1;
    
    // Check if file already exists
    if (file_exists($targetFile)) {
        echo "File already exists.";
        $uploadOk = 0;
    }
    
    // Check file size
    if ($_FILES["fileToUpload"]["size"] > 100000000) {  // Adjust the size limit as per your requirements
        echo "File size exceeds the limit.";
        $uploadOk = 0;
    }
    
    // Upload the file if all checks pass
    if ($uploadOk == 1) {
        if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $targetFile)) {
            echo "File uploaded successfully.";
        } else {
            echo "Error uploading file.";
        }
    }
}
?>
