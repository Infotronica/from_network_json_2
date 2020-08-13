<?php
    header("Content-Type: text/html;charset=utf-8");
    ini_set("display_errors", "On");
    error_reporting(E_ALL);

    $remoteFolder=$_POST["remoteFolder"]; // receive remoteFolder parameter via POST
    $remoteFile=$_POST["remoteFile"]; // receive remoteFile parameter via POST
    $fullName=$remoteFolder.'/'.$remoteFile; // concat for fullName
    if(!is_dir($remoteFolder)) // if the folder does not exists create it
    {
        mkdir($remoteFolder,0777);
    }

    if (file_exists($fullName)) // if the file already exists delete it
    {
        unlink($fullName);
    }
    $fileContent=$_POST["fileContent"];  // receive the content of file svg in the fileContent parameter via POST
    $fileContent=base64_decode($fileContent); // decode from base 64
    $fileContent=base64_decode($fileContent); // decode again

    $fp=fopen($fullName,"w");  // write the fileContent in a new file in the server
    fputs($fp,$fileContent);  // this is a copy of the svg file
    fclose($fp);

    $fileContent=file_get_contents($fullName, false); // read the new svg file created for sent
    echo $fileContent; // return the data, this data are received for networkReply in the client
?>
