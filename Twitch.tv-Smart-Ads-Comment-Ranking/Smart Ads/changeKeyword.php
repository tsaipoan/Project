<?php
//change the key word if the time is out
date_default_timezone_set("America/Detroit");
function get_url_contents($url){
    $crl = curl_init();
    $timeout = 5;
    curl_setopt ($crl, CURLOPT_URL,$url);
    curl_setopt ($crl, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt ($crl, CURLOPT_CONNECTTIMEOUT, $timeout);
    $ret = curl_exec($crl);
    curl_close($crl);
    return $ret;
}

$dsnMsg = 'mysql:host=messagebase.c0dpqj5xfw8m.us-east-1.rds.amazonaws.com;port=3306;dbname=messageBase';
$usernameMsg = 'dBAdmin';
$passwordMsg = 'amazonisamazing';
$dsnAdv = 'mysql:host=adv.c0dpqj5xfw8m.us-east-1.rds.amazonaws.com;port=3306;dbname=AdvKeyWords';
$usernameAdv = 'dbadmin';
$passwordAdv = 'amazonisamazing';
try {
    $dbhMsg = new PDO($dsnMsg, $usernameMsg, $passwordMsg);
} catch(PDOException $e) {
    die('Could not connect to message database:<br/>' . $e);
}
try {
    $dbhAdv = new PDO($dsnAdv, $usernameAdv, $passwordAdv);
} catch(PDOException $e) {
    die('Could not connect to advertisement database:<br/>' . $e);
}

$channel = '';

if (isset($_REQUEST['c'])){
    $channel = $_REQUEST['c'];
}
if (isset($_POST['c'])){
    $channel = $_POST['c'];
}

foreach($dbhAdv->query('SELECT inserted FROM '.$channel.' LIMIT 1') as $row) {
    $time = $row[0];
}
/*
echo "db time: ";
var_dump($time);
echo "code time: ";
var_dump(date("H:i:s"));
*/
$localTime = date("H:i:s");

//if the last click time is <= 9 seconds, keep this ad running (exit)
if((strtotime($localTime)-strtotime($time)) <= 9){
    echo "lengthen";
    exit();
}

$speechParts = array('noun', 'verb'); //adjective? preposition? adverb?

$searches = array('playstation 4', 'hyperx headset', 'bluetooth mouse', 'echo', 'mechanical keyboard',

    'gaming mousepad', 'turtlebeach', 'gaming chair', 'wireless router', 'xbox one'); //10 random searches

//yandex dictionary username: capstone2016
//passwd: amazonisamazing
$key = "dict.1.1.20160414T161047Z.2231f37526e4f5e7.b3a8e4ad35b524426b79f106e8b70148076ba7c1";
$search = "";
$msgAr =array();
foreach($dbhMsg->query('SELECT message FROM '.$channel.' LIMIT 1') as $row) {
    $search = $row[0];
    $msgAr = explode(" ", $search);
}
$search = "";
foreach ($msgAr as $word) {
    $api = "https://dictionary.yandex.net/api/v1/dicservice.json/lookup?key=$key&lang=en-en&text=$word";
    $json = get_url_contents($api);
    $json = json_decode($json, true);
    $info = $json["def"][0];
    if (isset($info["pos"])) //if the word is in the dictionary
    {
        $part = $info["pos"];
        echo $word.' = '.$part.", ";
        if(in_array($part, $speechParts)){ //if the word is a noun or verb
            $search.=$word." ";
        }
    }
    /*else if(ctype_alnum($word)){ //if the word contains only letters and numbers (to avoid emoticons made of html)
        $search.=$word." ";
    }*/
}

if($search ==""){
    $search = $searches[rand(0,9)]; //selects a random search from searches array if no comment search available
}

//echo $search."<br>";

//creating SQL tables for ad popularity (number of clicks) and increasing ad lifetime
$dbhAdv->query("CREATE TABLE IF NOT EXISTS " . $channel . " (id int primary key not null, Keyword varchar(500), clicks int, viewers int, inserted time)");

foreach($dbhAdv->query('SELECT Keyword FROM '.$channel.' LIMIT 1') as $row) {
    $search2 = $row[0];
}
$search2 = preg_replace('/\s+/', '_', $search2); //underscore instead of spaces
$dbhAdv->query("DROP TABLE IF EXISTS ". $channel . $search2 . "Popularity");

$dbhAdv->query('DELETE FROM '.$channel);
$dbhAdv->query('INSERT INTO '.$channel . '(Keyword, clicks, viewers, inserted) VALUES("' . $search . '", 0, 0, "'.date("H:i:s").'")');

//echo "<br>";
var_dump($search);
