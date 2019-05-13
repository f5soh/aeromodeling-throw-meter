const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html><head>
<meta http-equiv="content-type" content="text/html; charset=utf-8">
<style>
body { font: 1em sans-serif;}
#header {
padding : 0px 15px;
text-align : left;
border : black solid 2px;
background : #1abc9c;
color : white;
font-size : 1em;
border-radius : 20px 20px 0px 0px;
}
#settings {
padding : 6px 15px;
border : black solid 2px;
background-color : #f4e969;
}
#measurements {
padding : 6px 15px;
border : black solid 2px;
background-color : #6adbe8;
border-radius :  0px 0px 20px 20px;
}
#CordeValue, #AngleValue, #DebatValue {
text-align : right;
display : inline-block;
font : bold 2em sans-serif;
margin : 4px 4px;
border-radius : 8px;
padding : 6px 10px;
background-color : #cdf8fd;
width : 150px;
}
#CordeValue {
width : 75px;
}
.label {
display : inline-block;
white-space : nowrap;
text-align : right;
font-size : 1.5em;
width : 140px;
}
.unit {
display : inline-block;
text-align : left;
font-size : 1.5em;
width : 126px;
}
.button {
border : none;
color : white;
padding : 11px 4px;
text-align : center;
text-decoration : none;
white-space : nowrap;
display : inline-block;
font-size : 1em;
margin : 6px 2px;
border-radius : 10px;
cursor : pointer;
}
.button1 { background-color: #4caf50; width:73px;}
.button2 { background-color: #4c86af; width:110px;}
</style>
<title>ESP Angle meter</title>
</head><body>
<div id="header"><h1>ESP Angle meter</h1></div>
<div id="settings">
<button class="button button1" type="button" onclick="sendData(-10)">-10</button>
<button class="button button1" type="button" onclick="sendData(-1)">-1</button>
<button class="button button1" type="button" onclick="sendData(1)">+1</button>
<button class="button button1" type="button" onclick="sendData(10)">+10</button>
<button class="button button2" type="button" onclick="sendData(302)">Load</button>
<button class="button button2" type="button" onclick="sendData(301)">Save</button>
<br>
<span class="label">Corde :</span><span id="CordeValue">0</span><span class="unit">mm</span>
</div>
<div id="measurements">
<span class="label">Angle :</span><span id="AngleValue">0</span><span class="unit">degrés</span><button class="button button2" type="button" onclick="sendData(0)">Init Angle</button><br>
<span class="label">Débat. :</span><span id="DebatValue">0</span><span class="unit">mm</span>
</div>
<script>
function sendData(value) {
var xhttp = new XMLHttpRequest();
xhttp.open("GET", "setData?Datastate="+value, true);
xhttp.send();
getData();
}

setInterval(function() {
// Call a function repetatively
getData();
}, 300); //300ms update rate

function getData() {
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
if (this.readyState == 4 && this.status == 200) {
var str_in = this.responseText;
var words = str_in.split(':');
document.getElementById("AngleValue").innerHTML = words[0];
document.getElementById("DebatValue").innerHTML = words[1];
document.getElementById("CordeValue").innerHTML = words[2];
}
};
xhttp.open("GET", "readData", true);
xhttp.send();
}
</script>
</body></html>
)=====";
