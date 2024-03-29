<?php
include 'config.php';
    $ac_query = "SELECT * FROM `timer` WHERE `equipment`='ac'";
    $ac_data = mysqli_query($conn, $ac_query);
    $AC_data = mysqli_fetch_assoc($ac_data);
    $curr_ac_ontime = $AC_data['ontime'];
    echo "AC ON time: ".$curr_ac_ontime;
?>