<html>
<head>
<title>My Room Temperature</title>
<style>
body {background-image:url("pattern.gif");}

.center{
width:350px;
height:300px;
padding:0px;
border:0px solid gray;
border-radius: 10px ;
margin:10px; 
position: fixed;
top: 50%;
left: 50%;
margin-top: -150px;
margin-left: -175px;
opacity:0.7;
background-color:#B38D27;}

.shadow{
width:0;
height:0;
padding:0px;
border:0px solid gray;
border-radius: 10px ;
margin:10px; 
position:fixed;
top: 50%;
left: 50%;
margin-top: -235px;
margin-left: -150px;
background-color:#AEB0B5;}

.temptext{
margin-top:40px;
text-align:center;
font-size:80px;
color:#ffffff;}

.datetext{
margin-top:30px;
text-align:center;
font-size:15px;
color:#ffffff;}
</style>

<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.3.0/jquery.min.js"></script> 
<script> 
var auto_refresh = setInterval(
function()
{
$('#dates').load('dates.php');
$('#temperature').load('temperature.php');
}, 1000);
</script>

</head>

<body>
<div class="shadow"/>
<div class="center">
<div class="temptext" id="temperature">
</div>

<div class="datetext" id="dates">
</div>
</div>
</body>
</html>