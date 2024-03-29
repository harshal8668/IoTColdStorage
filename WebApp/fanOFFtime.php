<?php
    include 'config.php';
    $fan_query = "SELECT * FROM `timer` WHERE `equipment`='fan'";
    $fan_data = mysqli_query($conn, $fan_query);
    $FAN_data = mysqli_fetch_assoc($fan_data);
    $curr_fan_offtime = $FAN_data['offtime'];
    echo "Fan OFF time: ".$curr_fan_offtime;


?>