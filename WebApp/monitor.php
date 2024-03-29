<?php
include 'config.php';

session_start();
if (!isset($_SESSION['loggedin']) || $_SESSION['loggedin'] != true) {
  header("location:index.php");
  exit;
} else {
  $query = "SELECT * FROM maintainance";
  $data = mysqli_query($conn, $query);
  $rows = mysqli_num_rows($data);
  if ($rows > 0) {
    while ($curr_detail = mysqli_fetch_assoc($data)) {
      $temp = $curr_detail['temp'];
      $hum = $curr_detail['hum'];
      $gas = $curr_detail['gas'];
    }
  } else {
    $temp = 'NA';
    $hum = 'NA';
    $gas = 'NA';
  }
}

?>

<!DOCTYPE html>
<html lang="en">

<head>
  <!-- Required meta tags -->
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script src="darkmode.js"></script>
  <!-- Bootstrap CSS -->
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
  <link rel="stylesheet" href="style.css">
  <title>Chamber 1</title>
</head>

<body>
  <header>
    <nav class="container">
      <ul class="nav justify-content-end">
        <li class="nav-item">
          <a class="nav-link active" aria-current="page" href="home.php"><img src="Images/home.png" alt="Home"> Home</a>
        </li>
        <li class="nav-item">
          <a class="nav-link active" aria-current="page" href="logout.php"><img src="Images/profile.png" alt="Home">LogOut</a>
        </li>

        <li class="nav-item darkMode">
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
    <h5>Maintainence</h5>
    <div class="deviceContainer">
      <div class="deviceCard">
        <h3>Temperature</h3>
        <img src="Images/temp.png" alt="" width="50px" height="50px">
        <p id='curr_temp' style="font-size: 30px;"><?php echo $temp ?><sup>o</sup>C</p>
      </div>

      <div class="deviceCard">
        <h3>Humidity</h3>
        <img src="Images/humidity.png" alt="" width="50px" height="50px">
        <p id='curr_hum' style="font-size: 30px;"><?php echo $hum ?> %</p>

      </div>

      <div class="deviceCard">
        <h3>Gas</h3>
        <img src="Images/gas.png" alt="" width="50px" height="50px">
        <p id='curr_gas' style="font-size: 30px;"><?php echo $gas ?> cf</p>
      </div>
    </div>
  </main>

  <link rel="stylesheet" href="override.css">
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>

  <script>
    setTimeout(function() {
      location.reload();
    }, 2000);
  </script>
</body>

</html>