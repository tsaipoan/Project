<?php
//update the time in the database
date_default_timezone_set("America/Detroit");
$dsn = 'mysql:host=adv.c0dpqj5xfw8m.us-east-1.rds.amazonaws.com;port=3306;dbname=AdvKeyWords';
$username = 'dbadmin';
$password = 'amazonisamazing';
try {
    $dbh = new PDO($dsn, $username, $password);
} catch(PDOException $e) {
    die('Could not connect to the database:<br/>' . $e);
}
$channel = '';
if (isset($_REQUEST['channel'])){
    $channel = $_REQUEST['channel'];
}

$time = date("H:i:s");
//echo $time;

$ret = $dbh->query('UPDATE '.$channel.' SET inserted = "'.$time . '" WHERE id=0');
//var_dump($ret, 'UPDATE '.$channel.' SET inserted = "'.$time . '" WHERE id=0');