<?php
/**
 * Created by PhpStorm.
 * User: cse498
 * Date: 4/3/16
 * Time: 3:18 PM
 */

require 'vendor/autoload.php';

use Aws\Ec2\Ec2Client;

$instance_id = $argv[1];
$channel_name = $argv[2];
$public_key = $argv[3];

$ec2Client = new Ec2Client(array(
    'credentials' => array(
        'key' => 'AKIAJNWU4ICG4BZR4SIQ',
        'secret' => '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'),
    'region' => 'us-east-1',
    'version' => 'latest'
));

$ec2Client->waitUntil("InstanceRunning", array('InstanceIds'=>array($instance_id)));

$result = $ec2Client->describeInstances(array(
    'InstanceIds' => array($instance_id),
    'MaxResults' => 1
));

$instance_dns = $result['Reservations'][0]['Instances'][0]['PublicDnsName'];
var_dump($instance_dns);

$ssh_base = "ssh -oUserKnownHostsFile=/dev/null -i {$public_key} ubuntu@{$instance_dns} '/home/ubuntu/run.sh'";

exec($ssh_base);
