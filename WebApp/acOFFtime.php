<?php
include 'config.php';
    $ac_query = "SELECT * FROM `timer` WHERE `equipment`='ac'";
    $ac_data = mysqli_query($conn, $ac_query);
    $AC_data = mysqli_fetch_assoc($ac_data);
    $curr_ac_offtime = $AC_data['offtime'];
    echo "AC Off time: ".$curr_ac_offtime;
?>