<?php
    header("Content-Type: text/html;charset=utf-8");
    ini_set("display_errors", "On");
    error_reporting(E_ALL);

    $remoteFolder=$_POST["remoteFolder"]; // receive remoteFolder parameter via POST
    $remoteFile=$_POST["remoteFile"]; // receive remoteFile parameter via POST
    $fullName=$remoteFolder.'/'.$remoteFile; // concat for fullName
    if(!is_dir($remoteFolder)) // if the folder does not exists return empty string
    {
        echo "";
    }

    if (!file_exists($fullName)) // if the file does not exists return empty string
    {
        echo "";
    }

    $fileContent=file_get_contents($fullName, false); // read the new svg file created for sent
    echo $fileContent; // return the data, this data are received for networkReply in the client
?>
