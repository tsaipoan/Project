<?php
//set up the value that PDO needs
$dsnMsg = 'mysql:host=messagebase.c0dpqj5xfw8m.us-east-1.rds.amazonaws.com;port=3306;dbname=messageBase';
$usernameMsg = 'dBAdmin';
$passwordMsg = 'amazonisamazing';
$dsn = 'mysql:host=adv.c0dpqj5xfw8m.us-east-1.rds.amazonaws.com;port=3306;dbname=AdvKeyWords';
$username = 'dbadmin';
$password = 'amazonisamazing';

//connect to the database
try {
    $dbh = new PDO($dsn, $username, $password);
} catch(PDOException $e) {
    die('Could not connect to the database:<br/>' . $e);
}
try {
    $dbhMsg = new PDO($dsnMsg, $usernameMsg, $passwordMsg);
} catch(PDOException $e) {
    die('Could not connect to message database:<br/>' . $e);
}
$channel = '';
$search2 = '';
$pop_num = 0;
//get the channel
if (isset($_REQUEST['c'])){
    $channel = $_REQUEST['c'];
}

//find what we are searching for using POST
if(isset($_POST['search']) && $_POST['search'] != '')
{
    $search = $_POST['search'];

}
//get the search key word through database
else
{
    //$search = 'HyperX headset';
    $search = 'hyperx';

    //$dbh->query("CREATE TABLE IF NOT EXISTS " . $channel . " (id int primary key not null, Keyword varchar(500), clicks int, viewers int)");
    $dbh->query("CREATE TABLE IF NOT EXISTS " . $channel . " (id int primary key not null, Keyword varchar(500), clicks int, viewers int, inserted time)");

    foreach($dbh->query('SELECT Keyword FROM '.$channel.' LIMIT 1') as $row) {
        $search = $row[0];
    }
    $search2 = preg_replace('/\s+/', '_', $search);
    $dbh->query("CREATE TABLE IF NOT EXISTS ". $channel. $search2 ."Popularity (ip INT)");
    $pop = $dbh->query('SELECT COUNT(ip) FROM '. $channel. $search2 .'Popularity');

    foreach ($pop as $row) {
        $pop_num = $row[0];
    }
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
    $viewers = 0;
    $summary = "https://api.twitch.tv/kraken/streams?channel=" . $channel;
    $json = get_url_contents($summary);
    $json = json_decode($json, true);
    $info = $json["streams"][0];
    if (isset($info["viewers"]))
    {
        $viewers = $info["viewers"];
    }
    $dbh->query('UPDATE '.$channel.' SET clicks=' . $pop_num . ', viewers=' . $viewers . ' WHERE Keyword="' . $search . '"');

}

//set up the value we use in AmazonECS
$category = "All";

define('AWS_API_KEY', 'AKIAJU3VVP2BZIY3Q7PQ');
define('AWS_API_SECRET_KEY', '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');
define('AWS_ASSOCIATE_ID', 't0f44b-20');

require 'lib/AmazonECS.class.php';

//declare the amazon ECS class
$amazonEcs = new AmazonECS(AWS_API_KEY, AWS_API_SECRET_KEY, 'com', AWS_ASSOCIATE_ID);
$amazonEcs->page(1);
//tell the amazon class that we want an array, not an object
$amazonEcs->setReturnType(AmazonECS::RETURN_TYPE_ARRAY);

//search on Amazon
$response = $amazonEcs->category($category)->responseGroup('Large')->search($search);

?>

<!doctype html>
<html>
<head>
    <style>
        html, body, header, footer, nav, article, section, figure,
        figcaption, h1, h2, h3, ul, li, body, div, p, img {
            margin: 0;
            padding: 0;
            font-size: 100%;
            vertical-align: baseline;
            border: 0;
            overflow:hidden;
        }
        .popularity {
            position: absolute;
            width: 25px;
            height: 136px;
            float:left;
            text-align:center;
        }

        .thumb{
            margin-top: 4px;
            width: 20px;
            height: 20px;
            display:inline-block;
        }

        .light{
            width: 16px;
            height: 5px;
            display:inline-block;
        }
        body {
            width: 375px;
            text-align: center;
        }
        .ad {
            width: 359px;
            background: white;
        }

        .pic {
            display: inline-block;
            width: 100px;
            height: 100px;
            margin: 1em;
        }

        .pic img {
            height: 100%;
        }


        .text {
            padding-right: 10px;
            display: inline-block;
            width: 170px;
            height: 100px;
            margin: 1em;
            text-align: center;
        }

        .text p {
            padding-top: 5px;
            font-size: 1.2em;
            font-family: "Arial";
            height: 30%;
            text-overflow: ellipsis;
            white-space: nowrap;
        }

        ::-webkit-scrollbar {
            display: none;
        }

        .text img {
            padding-top: 5px;
            height: 60%;
        }

        a:link{
            color: black;
        }

        a:visited{
            color: black;
        }

    </style>
    <meta charset="utf-8">
    <title>AD</title>

</head>
<body>
<div class="ad-container">
    <div class="popularity">
        <?php
        //check that there are items in the response
        if (isset($response['Items']['Item']) ) {
            //display the popularity bar
            echo '<img class="thumb" src="pic/thumbsUp.png">';

            $dark_pos = 15 - $pop_num;
            for ($i = 1; $i <= 15; $i++) {
                if ($i <= $dark_pos) {
                    echo '<img class="light" src="pic/lightOvalSmall.png" style="position: relative; top: ' . 1.5 * $i . 'px">';
                } else {
                    echo '<img class="light" src="pic/darkOvalSmall.png" style="position: relative; top: ' . 1.5 * $i . 'px">';
                }
            }
        }
        else
        {
            $dbh->query('UPDATE '.$channel.' SET Keyword=' . '"fire"' . ' WHERE Keyword="' . $search . '"');
        }
        ?>
    </div>

    <?php
    if (isset($response['Items']['Item']) ) {
        echo '<a target="_blank" href="ad.post.php?url=' . $response['Items']['Item'][0]['DetailPageURL'] . '&c=' . $channel . $search2 . '">';
    }
    ?>
    <div class="ad">
        <div class="pic">
            <?php
            //display the ads
            if (isset($response['Items']['Item']) ) {
                if (isset($response['Items']['Item'][0]['LargeImage']['URL'])) {
                    echo '<img class="ad-pic" src="' . $response['Items']['Item'][0]['LargeImage']['URL'] . '"/>';
                }
            }
            ?>
        </div><div class="text">
            <?php
            if (isset($response['Items']['Item']) ) {
                echo '<p>' . $response['Items']['Item'][0]['ItemAttributes']['Title'] . '</p>';
                echo '<img src="pic/amazon.png"/>';
            }
            ?>


        </div>
    </div>
    <?php
    if (isset($response['Items']['Item']) ) {
        echo '</a>';
    }
    ?>
</div>

</body>
</html>
