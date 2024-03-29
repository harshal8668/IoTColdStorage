<?php
session_start();
if(!isset($_SESSION['loggedin']) || $_SESSION['loggedin']!=true){
  header("location:index.php");
  exit;
}

?>
<!doctype html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <!-- Bootstrap CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <script src="darkmode.js"></script>
    <title>Cold Storage</title>
    <link rel="stylesheet" href="style.css">

  </head>
  <body>
    <header>
          <nav class="container">
            <ul class="nav justify-content-end">
              <li class="nav-item">
                <a class="nav-link active" aria-current="page" href="home.php"><img src="Images/home.png" alt="Home">Home</a>
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

    <main class="WelcomeContainer">
      <h1 style="color: black;">Welcome</h1>
      <p class="username" style="text-align: center; font-size:20px ;color: black;"><?php echo $_SESSION['name']?></p>
      <p style="color: black;text-align:justify;">Lorem ipsum, dolor sit amet consectetur adipisicing elit. 
        Ratione quaerat soluta dolorem, saepe doloremque in obcaecati dignissimos fuga rem magni 
        distinctio dolore nam possimus excepturi. Ducimus consequatur enim fuga quae!</p>
      <div class="btngrp">
        <button onclick="window.location='control.php'">Chamber 1</button>
        <button onclick="window.location='control.php'">Chamber 2</button>
        <button onclick="window.location='control.php'">Chamber 3</button>
        <button onclick="window.location='control.php'">Chamber 4</button>
      </div>
    </main>
    
    <link rel="stylesheet" href="override.css">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
  </body>
</html>