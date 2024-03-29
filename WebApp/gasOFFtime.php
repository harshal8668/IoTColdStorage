<?php
include 'config.php';

    $gas_query = "SELECT * FROM `timer` WHERE `equipment`='gas'";
    $gas_data = mysqli_query($conn, $gas_query);
    $GAS_data = mysqli_fetch_assoc($gas_data);
    $curr_gas_offtime = $GAS_data['offtime'];
    echo "Gas OFF time: ".$curr_gas_offtime;



?>