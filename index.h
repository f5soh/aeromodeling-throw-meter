const char MAIN_page[] PROGMEM = R"=====(
<html><head>
<meta http-equiv="content-type" content="text/html; charset=utf-8">
<style>
.header {
padding: 10px;
text-align: left;
background: #1abc9c;
color: white;
font-size: 1em;
}
#measurements {
  padding : 20px;
  border : 2px solid black;
  background-color: #6adbe8;
}
#settings {
  padding : 20px;
  border : 2px solid black;
  background-color: #f4e969;
}
.button {
border: none;
color: white;
padding: 20px;
text-align: center;
text-decoration: none;
display: inline-block;
font-size: 1,5em;
margin: 4px 2px;
border-radius: 8px;
cursor: pointer;
}
.button1 { background-color: #4caf50;}
.button2 { background-color: #4c86af;}

span {
text-align: right;
text-decoration: none;
display: inline-block;
font-size: 2em;
margin: 4px 2px;
border-radius: 8px;
padding:16px;
background-color: #cdf8fd;
width: 15%;
}
</style>
<title>ESP Angle meter</title>
</head><body>
<div class="header"><h1>ESP Angle meter</h1></div>
<div id="settings">
<button class="button button1" type="button" onclick="sendData(-10)">-10</button>
<button class="button button1" type="button" onclick="sendData(-1)">-1</button>
<button class="button button1" type="button" onclick="sendData(1)">+1</button>
<button class="button button1" type="button" onclick="sendData(10)">+10</button>
<br>
Corde : <b><span id="CordeValue">0</span> mm </b><button class="button button2" type="button" onclick="sendData(301)">Save</button><button class="button button2" type="button" onclick="sendData(302)">Load</button>
</div>
<div id="measurements">
Angle  : <b><span id="AngleValue">0</span> degrés </b><button class="button button2" type="button" onclick="sendData(0)">Init Angle</button><br>
Débat. : <b><span id="DebatValue">0</span> mm</b><br>
</div>

<script>
function sendData(value) {
var xhttp = new XMLHttpRequest();
xhttp.open("GET", "setData?Datastate="+value, true);
xhttp.send();
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
