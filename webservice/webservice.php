<?php
    header("Content-Type: text/html;charset=utf-8");
    ini_set("display_errors", "On");
    error_reporting(E_ALL);

    $server="localhost"; // always is localhost
    $sql="select * from `countries list`"; // default value for $sql
    $usr_db=""; // default value for $usr_db
    $pwd_db=""; // default value for $usr_db
    $bd_name=""; // default value for
    $imax=""; // default value for
    $table_max=""; // default value for

    $sql=$_POST["sql"]; // receive sql parameter via POST
    $usr_db=$_POST["usr_db"]; // receive usr_db parameter via POST
    $pwd_db=$_POST["pwd_db"]; // receive pwd_db parameter via POST
    $bd_name=$_POST["db_name"]; // receive db_name parameter via POST

    if (isset($_POST["imax"]))
    {
        $imax=$_POST["imax"]; // receive imax parameter via POST
    }
    if (isset($_POST["table_max"]))
    {
        $table_max=$_POST["table_max"]; // receive table_max parameter via POST
    }

    $mysqli_main = mysqli_connect($server, $usr_db, $pwd_db, $bd_name); // connect to the server
    if (mysqli_connect_errno())
    {
        printf("Fail to connect: %s<br>", mysqli_connect_error());
        exit();
    }

    $query_main = mysqli_query($mysqli_main, $sql); // exec query sql received
    if ($table_max!="" && $imax!="") // if the $table_max and $imax variables are not empty
    { // obtain the last index in the table "select max(icountry) as imax from `countries list`"
        $sql="select max(`".$imax."`) as `".$imax."` from `".$table_max."`";
        $query_main = mysqli_query($mysqli_main, $sql); // exec query for get last index
        $row=mysqli_fetch_assoc($query_main); // fetches into a plain data

        $i=$row[$imax]; // the last index
        echo $i; // return the last index without usign json format, this data are received for networkReply in the client
        return;
    }

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
