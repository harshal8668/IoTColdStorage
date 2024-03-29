<?php
include 'config.php';
if($_SERVER['REQUEST_METHOD']==='POST'){
    $email=$_POST['email'];
    $pwd=$_POST['password'];
    $cnfmpwd=$_POST['cnfmpassword'];
    if(empty($email)||empty($password)||empty($cnfmpwd)){
        $error_string='All fields are mandatory';
    }
    elseif($pwd==$cnfmpwd){
        $update_pwd_query='UPDATE `userdata` SET `password`= $pwd WHERE `email`=$email';
        $res=mysqli_query($conn,$update_pwd_query);
        $error_string='Password update successful.';
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

    <title>Cold Storage</title>

  </head>
  <body>
    <header>
          <nav class="container">
            <ul class="nav justify-content-end">
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

    <main class="LoginContainer" >
      <form action="#" method="POST" class="form_main" autocomplete="off">
        <h1>Password Reset</h1>
        <p ><?php echo $error_string?></p>
        <div class="inputContainer">
          <svg class="inputIcon" xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="#2e2e2e" viewBox="0 0 16 16">
              <path d="M13.106 7.222c0-2.967-2.249-5.032-5.482-5.032-3.35 0-5.646 2.318-5.646 5.702 0 3.493 2.235 5.708 5.762 5.708.862 0 1.689-.123 2.304-.335v-.862c-.43.199-1.354.328-2.29.328-2.926 0-4.813-1.88-4.813-4.798 0-2.844 1.921-4.881 4.594-4.881 2.735 0 4.608 1.688 4.608 4.156 0 1.682-.554 2.769-1.416 2.769-.492 0-.772-.28-.772-.76V5.206H8.923v.834h-.11c-.266-.595-.881-.964-1.6-.964-1.4 0-2.378 1.162-2.378 2.823 0 1.737.957 2.906 2.379 2.906.8 0 1.415-.39 1.709-1.087h.11c.081.67.703 1.148 1.503 1.148 1.572 0 2.57-1.415 2.57-3.643zm-7.177.704c0-1.197.54-1.907 1.456-1.907.93 0 1.524.738 1.524 1.907S8.308 9.84 7.371 9.84c-.895 0-1.442-.725-1.442-1.914z"></path>
          </svg>
          <input type="text" name="email" class="inputField" id="username" placeholder="Email">
        </div>
        
        <div class="inputContainer">
          <svg class="inputIcon" xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="#2e2e2e" viewBox="0 0 16 16">
            <path d="M8 1a2 2 0 0 1 2 2v4H6V3a2 2 0 0 1 2-2zm3 6V3a3 3 0 0 0-6 0v4a2 2 0 0 0-2 2v5a2 2 0 0 0 2 2h6a2 2 0 0 0 2-2V9a2 2 0 0 0-2-2z"></path>
          </svg>
          <input type="password" name="password" class="inputField" id="password" placeholder="Password">
        </div>

        <div class="inputContainer">
          <svg class="inputIcon" xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="#2e2e2e" viewBox="0 0 16 16">
            <path d="M8 1a2 2 0 0 1 2 2v4H6V3a2 2 0 0 1 2-2zm3 6V3a3 3 0 0 0-6 0v4a2 2 0 0 0-2 2v5a2 2 0 0 0 2 2h6a2 2 0 0 0 2-2V9a2 2 0 0 0-2-2z"></path>
          </svg>
          <input type="password" name="cnfmpassword" class="inputField" id="password" placeholder="Confirm Password">
        </div>
        
        <button type="submit" name="login" id="button">Reset</button>
        <a class="forgotLink" href="index.php">Back to Login</a>
       
      </form>
    
    </main>
    
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
    <link rel="stylesheet" href="style.css">
  </body>
</html>