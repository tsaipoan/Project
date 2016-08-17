<?php
/**
 * Created by PhpStorm.
 * User: Chaz Schooler
 * Date: 3/27/2016
 * Time: 10:55 PM
 */

require 'vendor/autoload.php';
include('Net/SSH2.php');

use Aws\Ec2\Ec2Client;

function checkTranscriptionExists($db, $channel)
{
    $results = $db->query("SELECT * FROM `ChannelTranscription`.`active_transcription` WHERE channel_name='$channel'");

    if($results->rowCount() == 0)
    {
        return false;
    }

    $channel_result = $results->fetch(PDO::FETCH_ASSOC);

    return $channel_result['active'] != 0;
}

function setTranscriptionExists($db, $channel, $instance)
{
    $results = $db->query("SELECT * FROM `ChannelTranscription`.`active_transcription` WHERE channel_name='$channel'");

    if($results->rowCount() == 0)
    {
        //Insert new record
        $db->exec("INSERT INTO `ChannelTranscription`.`active_transcription` (`channel_name`, `active`, `instance_id`) VALUES ('$channel', '1', '$instance')");
    }
    else
    {
        //Update old record
        $obj = $results->fetch(PDO::FETCH_ASSOC);
        $id = $obj['id'];
        $db->exec("UPDATE `ChannelTranscription`.`active_transcription` SET `active`='1', `instance_id`='$instance' WHERE `id`='$id'");
    }
}


function initiateTranscriptionAndRanking($channel_name)
{
    $channel_name = strtolower($channel_name);
    $database_connection = new PDO("mysql:host=adv.c0dpqj5xfw8m.us-east-1.rds.amazonaws.com;port=3306", "dbadmin", "amazonisamazing");
    if(checkTranscriptionExists($database_connection, $channel_name))
    {
        return;
    }
    $ec2Client = new Ec2Client(array(
        'credentials' => array(
            'key' => 'AKIAJNWU4ICG4BZR4SIQ',
            'secret' => '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'),
        'region' => 'us-east-1',
        'version' => 'latest'
    ));

    $keyPairName = 'transcription-key';
    $saveKeyLocation = "{$keyPairName}.pem";
    if(!file_exists($saveKeyLocation))
    {
        //Create and store an ssh key
        $result = $ec2Client->createKeyPair(array(
            'KeyName' => $keyPairName
        ));

        file_put_contents($saveKeyLocation, $result['keyMaterial']);
        chmod($saveKeyLocation, 0600);

        unset($result);
    }


    $result = $ec2Client->runInstances(array(
        'ImageId' => 'ami-2bf6e241',
        'MinCount' => 1,
        'MaxCount' => 1,
        'InstanceType' => 't2.medium',
        'KeyName' => $keyPairName,
        'SecurityGroups' => array("Transcription Security")
    ));

    $instance_id = $result['Instances'][0]['InstanceId'];

    $ec2Client->waitUntil("InstanceRunning", array('InstanceIds'=>array($instance_id)));

    $result = $ec2Client->describeInstances(array('InstanceIds' => array($instance_id)));

    $instance_dns = $result['Reservations'][0]['Instances'][0]['PublicDnsName'];

    $ssh = new Net_SSH2($instance_dns);

    $key = new Crypt_RSA();
    $key->loadKey(file_get_contents($saveKeyLocation));
        
    $ssh->login('ubuntu', $key);

    $ssh->exec("/home/ubuntu/run.sh $channel_name");

    setTranscriptionExists($database_connection, $channel_name, $instance_id);
}

