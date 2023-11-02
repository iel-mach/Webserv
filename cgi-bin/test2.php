<?php
// Check if query parameters are present
// while(1);
if (isset($_GET['name']) && isset($_GET['sname'])) {
    // Retrieve query parameters
    $name = $_GET['name'];
    $sname = $_GET['sname'];

    // Set cookies
    // setcookie("firstName", $name, time() + (86400 * 1)); // Expires in 1 day
    // setcookie("familyName", $sname, time() + (86400 * 1)); // Expires in 1 day
    setcookie("name", $name);
    setcookie("sname",    $sname);

    // Print cookie values
    echo "First Name: " . $name . "<br>";
    echo "Family Name: " . $sname . "<br>";
}
?>