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
padding : 10px 15px;
border : black solid 2px;
background-color : #f4e969;
}
#buttons {
display : inline-block;
vertical-align: top;
}
#chord {
display : inline-block;
}

.values {
display : inline-block;
white-space : nowrap;
}
#measurements {
padding : 10px 15px;
border : black solid 2px;
background-color : #6adbe8;
border-radius :  0px 0px 20px 20px;
}
#ChordValue, #AngleValue, #ThrowValue, #MinThrowValue, #MaxThrowValue, #AngleValue2, #ThrowValue2, #MinThrowValue2, #MaxThrowValue2 {
text-align : right;
display : inline-block;
font : bold 2em sans-serif;
margin : 4px 4px;
border-radius : 8px;
padding : 6px 10px;
background-color : #cdf8fd;
width : 140px;
}
#ChordValue, #ThrowValue, #MinThrowValue, #MaxThrowValue, #ThrowValue2, #MinThrowValue2, #MaxThrowValue2 {
width : 100px;
}

.label, .label2 {
display : inline-block;
white-space : nowrap;
text-align : right;
font-size : 1.5em;
width : 90px;
}
.label2 {
width : 90px;
}
.unit {
display : inline-block;
text-align : left;
font-size : 1.5em;
width : 50px;
}
.button {
border : none;
color : white;
padding : 11px 4px;
text-align : center;
text-decoration : none;
white-space : nowrap;
display : inline-block;
font-size : 1.3em;
margin : 6px 2px;
border-radius : 10px;
cursor : pointer;
}
.button1 { background-color: #4caf50; width:82px;}
.button2 { background-color: #4c86af; width:120px;}
</style>
<title>ESP Angle meter</title>
</head><body>
<div id="header"><h1>ESP Angle meter</h1></div>
<div id="settings">
<div id="chord">
<button class="button button1" type="button" onclick="sendData(-10)">-10</button>
<button class="button button1" type="button" onclick="sendData(-1)">-1</button>
<button class="button button1" type="button" onclick="sendData(1)">+1</button>
<button class="button button1" type="button" onclick="sendData(10)">+10</button>
<br>
<span class="label">Chord:</span><span id="ChordValue">50</span><span class="unit">mm</span>
</div>
<div id="buttons">
<button class="button button2" type="button" onclick="sendData(302)">Load</button>
<button class="button button2" type="button" onclick="sendData(301)">Save</button><br>
<button class="button button2" type="button" onclick="sendData(304)">Init Angle</button>
<button class="button button2" type="button" onclick="sendData(303)">Min/Max</button>
</div>
</div>
<div id="measurements">
<div id="master">
<div class="values">
<span class="label">Angle:</span><span id="AngleValue">-180.00</span><span class="unit">deg</span><br>
<span class="label">Throw:</span><span id="ThrowValue">100</span><span class="unit">mm</span>
</div>
<div class="values">
<span class="label2">Max:</span><span id="MaxThrowValue">100</span><span class="unit">mm</span><br>
<span class="label2">Min:</span><span id="MinThrowValue">-100</span><span class="unit">mm</span>
</div>
</div>
<div id="slave">
<div class="values">
<span class="label">Angle2:</span><span id="AngleValue2">-180.00</span><span class="unit">deg</span><br>
<span class="label">Throw2:</span><span id="ThrowValue2">100</span><span class="unit">mm</span>
</div>
<div class="values">
<span class="label2">Max2:</span><span id="MaxThrowValue2">100</span><span class="unit">mm</span><br>
<span class="label2">Min2:</span><span id="MinThrowValue2">-100</span><span class="unit">mm</span>
</div>
</div>
</div>
<script>
function sendData(value) {
const xhttpcmd = new XMLHttpRequest();
xhttpcmd.open("GET", "setData?Datastate="+value, true);
xhttpcmd.send(null);
getData();
}

setInterval(function() {
// Call a function repetatively
getData();
}, 500); //500ms update rate

function getData() {
this.slave_found = "undefined";
const xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function(event) {
if (this.readyState === XMLHttpRequest.DONE && this.status === 200) {
var str_in = this.responseText;
var words = str_in.split(':');
document.getElementById("ChordValue").innerHTML = words[0];
document.getElementById("AngleValue").innerHTML = words[1];
document.getElementById("ThrowValue").innerHTML = words[2];
document.getElementById("MinThrowValue").innerHTML = words[3];
document.getElementById("MaxThrowValue").innerHTML = words[4];
// Slave device
document.getElementById("AngleValue2").innerHTML = words[5];
document.getElementById("ThrowValue2").innerHTML = words[6];
document.getElementById("MinThrowValue2").innerHTML = words[7];
document.getElementById("MaxThrowValue2").innerHTML = words[8];
if ((words[9] != "1") && (slave_found != "false")) {
  slave_found = "false";
  document.getElementById("slave").style.display = "none";
} else if ((words[9] != "0")) {
  slave_found = "true";
  document.getElementById("slave").style.display = "block"; 
}
}
};
xhttp.open("GET", "readData", true);
xhttp.send(null);
}
</script>
</body></html>
)=====";
