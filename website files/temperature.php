<?php
header('Content-type: text/html; charset=iso-8859-1');  
$con = mysql_connect("hostname","username","password");

if (!$con)
  {
  die('Could not connect: ' . mysql_error());
  }

mysql_select_db("database", $con);

$result = mysql_query("SELECT * FROM roomtemp");

while($row = mysql_fetch_array($result))
  {
  $temp = $row['temperature'];
  echo substr($temp,0,2), "°C";
  }

mysql_close($con);
?> 