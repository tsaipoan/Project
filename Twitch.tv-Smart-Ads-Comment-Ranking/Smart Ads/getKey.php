<?php
//print the ad key word
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
foreach($dbh->query('SELECT Keyword FROM '.$channel.' LIMIT 1') as $row) {
    echo $row[0];
}