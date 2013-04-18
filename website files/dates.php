<?php
date_default_timezone_set('Canada/Eastern');
$con = mysql_connect("hostname","username","password");
$date = date('D M d H:i', time());

if (!$con)
  {
  die('Could not connect: ' . mysql_error());
  }

mysql_select_db("database", $con);

$result = mysql_query("SELECT * FROM roomtemp");

while($row = mysql_fetch_array($result))
  {
  echo "Last Update: <br/>";
  echo $row['date'];
  $remoteDate = substr($row['date'], 0, 16);
  }
echo "<br />";
//echo "$date";

if (strcmp($date, $remoteDate) == 0) {
echo "<br />";
echo "system online";
}
else {
echo "<br />";
echo "system offline";
}

mysql_close($con);
?> 