<?php
    header("Content-Type: text/html;charset=utf-8");
    ini_set("display_errors", "On");
    error_reporting(E_ALL);

    $server="localhost"; // always is localhost
    $sql="select * from `countries list`"; // default value for $sql
    $usr_db="infotron_admin"; // default value for $usr_db
    $pwd_db="M7SWcVsUJa]#"; // default value for $usr_db
    $bd_name="infotron_countries"; // default value for

    $mysqli_main = mysqli_connect($server, $usr_db, $pwd_db, $bd_name); // connect to the server
    if (mysqli_connect_errno())
    {
        printf("Fail to connect: %s<br>", mysqli_connect_error());
        exit();
    }

    $query_main = mysqli_query($mysqli_main, $sql); // exec query sql received

    $i=0;
    $my_array=array(); // initialize my array
    while ($row=mysqli_fetch_array($query_main, MYSQLI_ASSOC)) // fetches the result set by copying it to an array
    {
        $my_array[$i++]=$row; // create a new array element with the fetched data
    }
    mysqli_close($mysqli_main); // close the result set

    if ($i==0) // if result set is empty i=0, then return empty string
    {
        echo "";
    }
    else
    {
        $json=json_encode($my_array); // encode the new array into json format
        echo $json; // return the data, this data are received for networkReply in the client
    }
?>
