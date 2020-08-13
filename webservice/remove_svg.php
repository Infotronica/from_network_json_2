<?php
    header("Content-Type: text/html;charset=utf-8");
    ini_set("display_errors", "On");
    error_reporting(E_ALL);

    $remoteFolder=$_POST["remoteFolder"]; // receive remoteFolder parameter via POST
    $remoteFile=$_POST["remoteFile"]; // receive remoteFile parameter via POST
    $fullName=$remoteFolder.'/'.$remoteFile; // concat for fullName
    unlink($fullName); // remove the svg file
?>
