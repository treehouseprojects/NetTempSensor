<?php
mysql_connect("hostname","username","password");
mysql_select_db("database");
$sql=mysql_query("SELECT * FROM roomtemp");
while($row=mysql_fetch_assoc($sql))
echo $row['temperature'], "&", $row['date'];
//$output[]=$row;
//print(json_encode($output));
mysql_close();
?>