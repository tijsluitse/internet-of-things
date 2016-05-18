// Code inspired by Linda
$("#buzzer-on").click(function(){
    $.get("http://tijsluitse.com/iot/eindopdracht/index.php",
   	{
        buzzer: "on"
    }
});
$("#buzzer-off").click(function(){
    $.get("http://tijsluitse.com/iot/eindopdracht/index.php",
    {
        buzzer: "off"
    }
});