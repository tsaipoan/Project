

<?php
$dsn = 'mysql:host=messagebase.c0dpqj5xfw8m.us-east-1.rds.amazonaws.com;port=3306;dbname=messageBase';
$username = 'dBAdmin';
$password = 'amazonisamazing';
$channel;

if (isset($_REQUEST['c'])){
    $channel = $_REQUEST['c'];
}

$dbh = new PDO($dsn, $username, $password);

try {
    $dbh = new PDO($dsn, $username, $password);
} catch(PDOException $e) {
    die('Could not connect to the database:<br/>' . $e);
}


?>



<!DOCTYPE html>
<html>
<head>
<script type=text/javascript>
    function scroll(){
        var a = document.getElementById('cmnts').contentWindow;
        a.scrollTo(0,200);
    }
</script>
<title>Chat</title>
<meta http-Equiv="Cache-Control" Content="no-cache">
<meta http-Equiv="Pragma" Content="no-cache">
<meta http-Equiv="Expires" Content="0">
<style>
.top {
     color: #7E7E7E;
     padding-left: 0.5em;
     font-family: "arial";
     font-size: 1em;
     font-weight: 200;
 }
p {
  padding-left: 0.5em;
  font-family: "arial";
  font-size: 1em;
}
html,body {
    font-family: 'Roboto', sans-serif;
    background-color: #f2f2f2;
    color: hsla(0, 0%, 12%, .95);
    font-size: 16px;
}
#chat {
    left: 0;
    right: 0;
    padding: .5em;
}
.chat-line {
    -webkit-transition: all 1s ease-in;
    -moz-transition: all 1s ease-in;
    -ms-transition: all 1s ease-in;
    -o-transition: all 1s ease-in;
    transition: all 1s ease-in;
    padding-top: 5px;
}
.chat-line[data-faded] {
    opacity: .8;
}
.chat-line.chat-action {
}
.chat-line.chat-notice {
    opacity: .7;
    font-weight: 300;
}
.chat-line.chat-notice[data-level] {
}
.chat-line.chat-notice[data-level="-4"] {
    color: hsla(250, 80%, 65%, 1);
    font-style: italic;
}
.chat-line.chat-notice[data-level="-3"] {
    color: hsla(200, 80%, 50%, 1);
    font-style: italic;
}
.chat-line.chat-notice[data-level="-2"] {
    color: hsla(160, 80%, 50%, 1);
    font-style: italic;
}
.chat-line.chat-notice[data-level="-1"] {
    color: hsla(100, 80%, 50%, 1);
    font-style: italic;
}
.chat-line.chat-notice[data-level="1"] {
    color: hsla(55, 100%, 50%, 1);
}
.chat-line.chat-notice[data-level="2"] {
    color: hsla(30, 100%, 50%, 1);
    font-weight: 400;
}
.chat-line.chat-notice[data-level="3"] {
    color: hsla(0, 100%, 50%, 1);
    font-weight: 400;
}
.chat-line.chat-notice[data-level="4"] {
    color: hsla(0, 100%, 50%, 1);
    font-weight: 700;
}
.chat-line.chat-notice[data-faded] {
    opacity: .3;
}
.chat-line.chat-timedout {
    opacity: .2;
    font-size: .75em;
    -webkit-transition: all 100ms ease-in;
    -moz-transition: all 100ms ease-in;
    -ms-transition: all 100ms ease-in;
    -o-transition: all 100ms ease-in;
    transition: all 100ms ease-in;
}
.chat-line.chat-cleared {
    opacity: .2;
    font-size: .33em;
    -webkit-transition: all 100ms ease-in;
    -moz-transition: all 100ms ease-in;
    -ms-transition: all 100ms ease-in;
    -o-transition: all 100ms ease-in;
    transition: all 100ms ease-in;
}
.chat-channel {
    margin-right: .375em;
    opacity: .6;
    font-weight: 300;
}
.chat-name {
    font-weight: 800;
}
.chat-colon {
    margin-right: .375em;
    opacity: .85;
}
.chat-line:not(.chat-action) .chat-colon:after {
    content: ':';
}
.chat-message {
    font-weight: 400;
}
.chat-line:not(.chat-action) .chat-message {
    color: inherit !important;
}

.chat-button {
    background:url(arrowUp.png) no-repeat;
    background-size: 15px 20px;
    /*border: 0px solid #black; */
    height: 19px;
    width: 15px;
    margin-right: 2px;
    border: none;
}



.emoticon {
    background-position: center center;
    background-repeat: no-repeat;
    margin: -5px 0;
    display: inline-block;
    vertical-align: middle !important;
    height: 1.5em;
}

.chat-badges {
    margin-right: .125em;
}
.chat-badges > div {
    margin-bottom: 1px;
    border-radius: 2px;
    height: 1em;
    min-width: 1em;
    display: inline-block;
    vertical-align: middle;
    background-size: contain;
    background-repeat: no-repeat;
    margin-right: .3em;
}

.chat-badge-mod {
    background-color: hsl(105, 89%, 36%);
    background-image: url(http://www.twitch.tv/images/xarth/badge_mod.svg);
}
.chat-badge-turbo {
    background-color: hsl(261, 43%, 45%);
    background-image: url(http://www.twitch.tv/images/xarth/badge_turbo.svg);
}
.chat-badge-broadcaster {
    background-color: hsl(0, 81%, 50%);
    background-image: url(http://www.twitch.tv/images/xarth/badge_broadcaster.svg);
}
.chat-badge-admin {
    background-color: hsl(40, 96%, 54%);
    background-image: url(http://www.twitch.tv/images/xarth/badge_admin.svg);
}
.chat-badge-staff {
    background-color: hsl(268, 55%, 13%);
    background-image: url(http://www.twitch.tv/images/xarth/badge_staff.svg);
}
.chat-badge-subscriber {
}
.chat-badge-bot {
    background-image: url(https://cdn.betterttv.net/tags/bot.png);
}


[class*="chat-delete"] {
}
.chat-delete-timeout {
}
.chat-delete-clear {
}

[class*="chat-hosting"] {
}
.chat-hosting-yes {
}
.chat-hosting-no {
}

[class*="chat-connection"] {
}
[class*="chat-connection-good"] {
}
[class*="chat-connection-bad"] {
}
.chat-connection-good-connecting {
}
.chat-connection-good-logon {
}
.chat-connection-good-connected {
}
.chat-connection-good-reconnect {
}
.chat-connection-bad-fail {
}
.chat-connection-bad-disconnected {
}

[class*="chat-room"] {
    font-size: .5em;
}
.chat-room-join {
}
.chat-room-part {
}

.chat-crash {
}

</style>
</head>

<body>
<div class="topComments">
    <div class="chat"
    <?php
    
    $i = 0;
    $dbh->query('DELETE FROM '.$channel.' WHERE timeSent < NOW()-INTERVAL 30 SECOND and message<>""');
    //$res = $dbh->query('SELECT * FROM '.$channel.' ORDER BY likes DESC LIMIT 5');
    $result = array();

    $result = $dbh->query('SELECT * FROM '.$channel.' ORDER BY likes DESC LIMIT 5');

    foreach($result as $row) {
        $i++;
        $usr = $row['username'];
        $msg = $row['message'];
        $rgb = $row['rgb'];
        $lik = $row['likes'];

        if(substr($rgb, 0, 1) != "r"){
            $rgb = "#".$rgb;
        }

        //echo '<div><p>'.$i.'.<span style="color: '.$row['rgb'].'">'.$row['username'].'</span>: '.$row['message'].'   ('.$row['likes'].' likes'.')</p></div>'; //etc...
        $html = <<<HTML
        <div class="chat-line" data-username="$usr" data-channel="$channel">
            <span class= "top$i">$i. </span>
            <span class="chat-name" style="color: $rgb;">$usr</span>
            <span class="chat-colon"></span>
            <span class="chat-message">$msg</span>
        </div>
HTML;
        echo $html;
        //array_push($result, array("message" => $row['message']));
    }

    //echo json_encode($result);
    ?>
    </div>
</div>
</body>
</html>
