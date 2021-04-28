<!DOCTYPE html>
<html lang="pl">

<head>
    <meta charset="UTF-8">
    <link rel="stylesheet" type="text/css" href="style.css">
    <title> Form </title>
</head>

<body>

    <?php 
          echo $_SERVER['SERVER_NAME'];
          echo "<br>";
          echo $_SERVER['PHP_SELF'];
          echo "<br>";
          echo $_SERVER['SCRIPT_FILENAME'];
          echo "<br>";
          echo $_SERVER['REMOTE_ADDR'];
          echo "<br>";
          echo $_SERVER['HTTP_USER_AGENT'];
          phpinfo();
          ?>

</body>

</html>