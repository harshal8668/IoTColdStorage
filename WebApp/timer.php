<?php
include 'config.php';

session_start();
if (!isset($_SESSION['loggedin']) || $_SESSION['loggedin'] != true) {
    header("location:index.php");
    exit;
} else {


    $ac_query = "SELECT * FROM `timer` WHERE `equipment`='ac'";
    $ac_data = mysqli_query($conn, $ac_query);
    $AC_data = mysqli_fetch_assoc($ac_data);
    $curr_ac_ontime = $AC_data['ontime'];
    $curr_ac_offtime = $AC_data['offtime'];

    $gas_query = "SELECT * FROM `timer` WHERE `equipment`='gas'";
    $gas_data = mysqli_query($conn, $gas_query);
    $GAS_data = mysqli_fetch_assoc($gas_data);
    $curr_gas_ontime = $GAS_data['ontime'];
    $curr_gas_offtime = $GAS_data['offtime'];

    $fan_query = "SELECT * FROM `timer` WHERE `equipment`='fan'";
    $fan_data = mysqli_query($conn, $fan_query);
    $FAN_data = mysqli_fetch_assoc($fan_data);
    $curr_fan_ontime = $FAN_data['ontime'];
    $curr_fan_offtime = $FAN_data['offtime'];


    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        if (isset($_POST['AcSubmit'])) {
            $setacon = $_POST['AcOn'];
            $setacoff = $_POST['AcOff'];
            $sql = "UPDATE `timer` SET `ontime`= $setacon, `offtime` = $setacoff WHERE `equipment` = 'ac'";
            mysqli_query($conn, $sql);
        }

        if (isset($_POST['GasSubmit'])) {
            $setgason = $_POST['GasOn'];
            $setgasoff = $_POST['GasOff'];
            $sql = "UPDATE `timer` SET `ontime`= $setgason, `offtime` = $setgasoff WHERE `equipment` = 'gas'";
            mysqli_query($conn, $sql);
        }

        if (isset($_POST['FanSubmit'])) {
            $setfanon = $_POST['FanOn'];
            $setfanoff = $_POST['FanOff'];
            $sql = "UPDATE `timer` SET `ontime`= $setfanon, `offtime` = $setfanoff WHERE `equipment` = 'fan'";
            mysqli_query($conn, $sql);
        }
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
                    <a class="nav-link active" aria-current="page" href="home.php"><img src="Images/home.png" alt=""> Home</a>
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
        <h5>Timer</h5>
        <form method="post" class="deviceContainer">
            <div class="deviceCard">
                <h3>Air Conditioner</h3>
                <p>Set on/off time</p>

                <div class="timerform">
                    <input type="number" placeholder="On Time" name="AcOn" id="">
                    <input type="number" placeholder="Off Time" name="AcOff" id="">
                    <button type="submit" name="AcSubmit" id="submit">Submit</button>
                </div>

                <p style="line-height: 7px; margin-top:20px;"  >Current time set</p>
                <p style="line-height: 7px;" id="curr_ac_ontime"></p>
                <p style="line-height: 7px;" id="curr_ac_offtime"></p>

            </div>

            <div class="deviceCard">
                <h3>Gas Valve</h3>
                <p>Set on/off time</p>
                <div class="timerform">
                    <input type="number" placeholder="On Time" name="GasOn" id="">
                    <input type="number" placeholder="Off Time" name="GasOff" id="">
                    <button type="submit" name="GasSubmit" id="submit">Submit</button>
                </div>
                <p style="line-height: 7px; margin-top:20px;" >Current time set</p>
                <p style="line-height: 7px;"  id="curr_gas_ontime"></p>
                <p style="line-height: 7px;" id="curr_gas_offtime"></p>
            </div>

            <div class="deviceCard">
                <h3>Exhaust Fan</h3>
                <p>Set on/off time</p>
                <div class="timerform">
                    <input type="number" placeholder="On Time" name="FanOn" id="">
                    <input placeholder="Off Time" type="number" class="input" name="FanOff" id="">
                    <button type="submit" name="FanSubmit" id="submit">Submit</button>
                </div>
                <p style="line-height: 7px; margin-top:20px;" >Current time set</p>
                <p style="line-height: 7px;"  id="curr_fan_ontime"></p>
                <p style="line-height: 7px;" id="curr_fan_offtime"></p>
            </div>
        </form>
    </main>

    <link rel="stylesheet" href="override.css">

    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
    
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.7.1/jquery.min.js"></script>
    <script>
        window.addEventListener('load', function() {
                <?php
                include 'config.php';
                $ac_query = "SELECT * FROM `timer` WHERE `equipment`='ac'";
                $ac_data = mysqli_query($conn, $ac_query);
                $AC_data = mysqli_fetch_assoc($ac_data);
                $curr_ac_ontime = $AC_data['ontime'];
                $curr_ac_offtime = $AC_data['offtime'];

                $gas_query = "SELECT * FROM `timer` WHERE `equipment`='gas'";
                $gas_data = mysqli_query($conn, $gas_query);
                $GAS_data = mysqli_fetch_assoc($gas_data);
                $curr_gas_ontime = $GAS_data['ontime'];
                $curr_gas_offtime = $GAS_data['offtime'];

                $fan_query = "SELECT * FROM `timer` WHERE `equipment`='fan'";
                $fan_data = mysqli_query($conn, $fan_query);
                $FAN_data = mysqli_fetch_assoc($fan_data);
                $curr_fan_ontime = $FAN_data['ontime'];
                $curr_fan_offtime = $FAN_data['offtime'];
                ?>
                document.getElementById('curr_ac_ontime').innerHTML = `On time: <?php echo $curr_ac_ontime ?> Min`;
                document.getElementById('curr_ac_offtime').innerHTML = `Off time: <?php echo $curr_ac_offtime ?> Min`;

                document.getElementById('curr_gas_ontime').innerHTML = `On time: <?php echo $curr_gas_ontime?> Min`;
                document.getElementById('curr_gas_offtime').innerHTML = `Off time: <?php echo $curr_gas_offtime ?> Min`;

                document.getElementById('curr_fan_ontime').innerHTML = `On time: <?php echo $curr_fan_ontime ?> Min`;
                document.getElementById('curr_fan_offtime').innerHTML = `Off time: <?php echo $curr_fan_offtime ?> Min`;

        });
    </script>
</body>

</html>