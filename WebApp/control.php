<?php
  include 'config.php';
  session_start();
  if(!isset($_SESSION['loggedin']) || $_SESSION['loggedin']!=true){
    header("location:index.php");
    exit;
}
else{
  
  $ac_status="SELECT `status` FROM `status` WHERE `equipments`='ac'";
  $res_ac=mysqli_query($conn,$ac_status);
  
  $gas_status="SELECT `status` FROM `status` WHERE `equipments`='gas'";
  $res_gas=mysqli_query($conn,$gas_status);
  
  $fan_status="SELECT `status` FROM `status` WHERE `equipments`='fan'";
  $res_fan=mysqli_query($conn,$fan_status);
  
  $ac_rows=mysqli_num_rows($res_ac);
  $gas_rows=mysqli_num_rows($res_gas);
  $fan_rows=mysqli_num_rows($res_fan);

  if($ac_rows==1 || $fan_rows==1 || $gas_rows==1){
    $ac_res_status=mysqli_fetch_assoc($res_ac);
    $gas_res_status=mysqli_fetch_assoc($res_gas);
    $fan_res_status=mysqli_fetch_assoc($res_fan);

    $AC=$ac_res_status['status'] == 1?'ON':'OFF';
    $GAS=$gas_res_status['status']== 1?'ON':'OFF';
    $FAN=$fan_res_status['status']== 1?'ON':'OFF';    
  }
  else{
    $AC='NA';
    $GAS='NA';
    $FAN='NA';
  }

  
}

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <!-- Bootstrap CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <script src="darkmode.js"></script>
    <title>Chamber 1</title>
    <link rel="stylesheet" href="style.css">

</head>
<body>
    <header>
        <nav class="container">
          <ul class="nav justify-content-end">
            <li class="nav-item">
              <a class="nav-link active" aria-current="page" href="home.php"><img src="Images/home.png" alt=""> Home</a>
            </li>
            <li class="nav-item">
                <a class="nav-link active" aria-current="page" href="logout.php"><img src="Images/profile.png" alt="Home">LogOut</a>
            </li>
            <li class="nav-item darkMode" >
              <input type="checkbox" name="toggle" id="toggle" onclick="ToggleDarkMode()">
              <label for="toggle" id="switch">
                <div class="Dark"></div>
                <div class="circle"></div>
                <div class="Light"></div>
              </label>
            </li>
          </ul>
        </nav>
        
    </header>

    <main class="OuterDeviceContainer">
        <h2>Chamber 1</h2>
        <div class="btngrp">
            <button onclick="window.location='control.php'">Controls</button>
            <button onclick="window.location='timer.php'">Timer</button>
            <button onclick="window.location='monitor.php'">Monitor</button>
        </div>

        <h5>Device Controls</h5>
        <div class="deviceContainer">
            <div class="deviceCard AC"> 
                <h3>Air Conditioner</h3>
                <p>Click on switch to On/Off</p>
                <a class="onoffbtn" href="onoff.php?eq='ac'"><button id="onoffbtn" ><?php echo $AC?></button></a>
            </div>

            <div class="deviceCard Gas">
                <h3>Gas Valve</h3>
                <p>Click on switch to On/Off</p>
                <a class="onoffbtn" href="onoff.php?eq='gas'"><button id="onoffbtn" ><?php echo $GAS?></button></a>
            </div>

            <div class="deviceCard Fan">
                <h3>Exhaust Fan</h3>
                <p>Click on switch to On/Off</p>
                <a  href="onoff.php?eq='fan'"><button id="onoffbtn" ><?php echo $FAN?></button></a>
            </div>
        </div>
    </main>

    <link rel="stylesheet" href="override.css">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>

    
</body>
</html>