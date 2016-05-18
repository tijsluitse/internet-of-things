<?php  
    
    //Inspired by http://blog.nyl.io/esp8266-led-arduino/ 
    $buzzer = $_GET['buzzer'];
    
    if($buzzer == "on") {  
      $file = fopen("output.txt", "w") or die("can't open file");
      fwrite($file, 'on');
      fclose($file);
    } else if ($buzzer == "off") {  
      $file = fopen("output.txt", "w") or die("can't open file");
      fwrite($file, 'off');
      fclose($file);
    }
    
    // Measurement of a value
    function lastDataStamp($array, $value) {
        foreach ($array as $key => $measurement) {
            if ($measurement['waste'] === $value) {
                return $measurement;
            }
        } 
    }

?>

<?php 
    
    // Code inspired by Leander
    if ($_SERVER["REQUEST_METHOD"] === "POST") {
      
        $data = $_POST["waste"];
        $timestamp = new DateTime();
        $time = $timestamp->format("Y-m-d H:i:s");
        $message = array("time" => $time, "waste" => $data);
        $inp = file_get_contents("waste.json");
        $tempArray = json_decode($inp);
        array_push($tempArray, $message);
        $jsonData = json_encode($tempArray);
        file_put_contents("waste.json", $jsonData);
    }
?>

<html>
    <head>
        <link rel="stylesheet" href="style.css">
        <meta name="viewport" content="width=device-width, initial-scale=1, minimum-scale=1, maximum-scale=1">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.2/jquery.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/1.0.2/Chart.min.js"></script>       
    </head>
    <body>
        
        <h1>Digital Waste Meter:</h1>

        <?php 
            $getData = file_get_contents("waste.json");
            $array = json_decode($getData, true);
            $last = end($array);
            $height = $last["waste"];
            if ($height == "4") {
                echo "<div class=\"ready\">Prullenbak legen!!</div>";            
            }
        ?>

        <section>
            <div id="chart">
                <canvas id="linechart" width="1000" height="400"></canvas>
            </div>
        </section>
        
        <section>
            <div class="buttons">
                <a href="?buzzer=off" class="aOff"><button id="buzzer-off" class="off">BUZZER OFF</button></a>
                <a href="?buzzer=on" class="aOn"><button id="buzzer-on" class="on">BUZZER ON</button></a>
            </div>
        </section>

    <script src="datachart.js"></script>

    </body>
</html>