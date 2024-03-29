<?php
include 'config.php';
$eq = $_GET['eq'];
// echo $eq;
$query = "SELECT `status` FROM `status` WHERE `equipments`=$eq";
$res = mysqli_query($conn, $query);

$rows = mysqli_num_rows($res);

if ($rows == 1) {
    $curr_status=mysqli_fetch_assoc($res)['status'];
    echo $curr_status;
    if($curr_status==1){
        $update_query = "UPDATE `status` SET  `status`= 0 WHERE `equipments`=$eq";
        mysqli_query($conn, $update_query);
        header('location:control.php');
    }
    else{
        $update_query = "UPDATE `status` SET  `status`= 1 WHERE `equipments`=$eq";
        mysqli_query($conn, $update_query);
        header('location:control.php');
    }    
} else {
    $AC = 'NA';
    $GAS = 'NA';
    $FAN = 'NA';
}
?>
