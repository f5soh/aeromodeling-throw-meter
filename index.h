const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html><head>
<meta http-equiv="content-type" content="text/html; charset=utf-8">
<style>
body {
font : 1em sans-serif;
margin : 0;
}
#header, #bottom {
padding : 5px 15px 0 5px;
text-align : left;
border : black solid 2px;
border-width : 2px 2px 0 2px;
background : #1abc9c;
font-size : 1em;
border-radius : 20px 20px 0 0;
}
#bottom {
padding : 5px 10px 5px 10px;
text-align : left;
border-width : 2px;
border-radius : 0 0 20px 20px;
}
#measurements, #settings, #calibrations, #system {
padding : 10px 0 0 15px;
border : black solid 2px;
min-height: 280px;
background-color : #6adbe8;
}
#settings {
background-color : #f4e969;
display : none;
}
#calibrations {
background-color : #69e969;
display : none;
}
#system {
background-color : #9f9f9f;
display : none;
}
#battery {
background-color : #66CD00;
border : 2px solid #000;
height : 48px;
display : inline-block;
float : right;
width : 24px;
margin : 6px;
margin-top : 10px;
margin-right : 10px;
border-radius : 6px;
}
#battery-used {
background-color : white;
border-radius : 4px 4px 0px 0px;
height : 25%;
}
#battery-used:after {
background-color : black;
border : 2px solid black;
content : "";
display : block;
height : 2px;
width : 8px;
position : relative;
left : 6px;
top : -6px;
border-radius : 4px;
}
#sysdata {
font : 1.5em sans-serif; 
}
#ChordValue, #AngleValue, #MinLimitValue, #MaxLimitValue, #ThrowValue, #MinThrowValue, #MaxThrowValue, #AngleValue2, #ThrowValue2, #MinThrowValue2, #MaxThrowValue2, #DiffValue, #XValue, #YValue, #ZValue, #XOffsetValue, #YOffsetValue, #ZOffsetValue {
text-align : right;
display : inline-block;
font : bold 2em sans-serif;
margin : 8px;
border-radius : 8px;
padding : 8px 8px;
background-color : #cdf8fd;
width : 100px;
}
#AngleValue, #AngleValue2 {
width : 140px;
}
#XValue, #YValue, #ZValue, #XOffsetValue, #YOffsetValue, #ZOffsetValue {
width : 135px;
}
.buttons {
display : inline-block;
vertical-align : top;
}
.values {
display : inline-block;
white-space : nowrap;
}
hr.separator {
border : 1px solid black;
width : 640px;
display : inline-block;
}
.tabbutton {
border : black solid 2px;
color : black;
padding : 15px 0;
text-align : center;
text-decoration : none;
white-space : nowrap;
display : inline-block;
font-size : 1.3em;
margin : 6px 6px -4px 6px;
border-radius : 20px 20px 0 0;
width : 20%;
cursor : pointer;
}
.tabmeasurements {
background-color : #6adbe8;
border-bottom : 4px solid #6adbe8;
}
.tabsettings {
background-color : #f4e969;
border-bottom : 4px solid #f4e969;
}
.tabcalibrations {
background-color : #69e969;
border-bottom : 4px solid #69e969;
}
.tabsystem {
background-color : #9f9f9f;
border-bottom : 4px solid #9f9f9f;
}
.tabbuttonaudio {
border : black solid 2px;
padding : 8px;
float : right;
margin : 6px 0px 0px 0px;
border-radius : 20px;
width : 80px;
background-color : #4c86af;
cursor : pointer;
}
.label, .label2, .label3, .label4, .label5 {
display : inline-block;
white-space : nowrap;
text-align : right;
font-size : 1.5em;
width : 100px;
}
.label2 {
width : 100px;
}
.label3 {
text-align : center;
width : 150px;
}
.label4 {
width : 60px;
}
.label5 {
width : 130px;
}
.unit {
display : inline-block;
text-align : left;
font-size : 1.5em;
width : 50px;
}
.button {
border : none;
color : black;
padding : 10px;
text-align : center;
text-decoration : none;
white-space : nowrap;
display : inline-block;
font-size : 1.3em;
margin : 4px;
border-radius : 10px;
background-color : #4c86af;
width : 160px;
cursor : pointer;
}
.button2 {
width : 180px;
}
/* Svg icons */
.icon-measurements, .icon-init_angle, .icon-minmax_reset, .icon-settings, .icon-calibrations, .icon-system, .img-esplogo {
display : inline-block;
vertical-align : -30%;
background-color : transparent;
}
.icon-measurements:before {
content : url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='32' height='32' version='1.1' viewBox='0 0 8.4666664 8.4666664' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'%3E%3Cg fill-rule='evenodd'%3E%3Cpath d='m0.60742 4.4805a0.30003 0.30003 0 1 0 0 0.59961h7.4141a0.30003 0.30003 0 1 0 0 -0.59961z' color='%23000000' color-rendering='auto' dominant-baseline='auto' image-rendering='auto' shape-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3Cg transform='matrix(.93154 .11113 -.094608 .79304 1.1201 .015298)'%3E%3Cpath d='m7.0664 1.3066l-0.095703 0.029297 0.83008 2.7012 0.095703-0.029297z' color='%23000000' color-rendering='auto' dominant-baseline='auto' image-rendering='auto' shape-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3Cpath d='m7.7311 3.6396l-0.24996-0.13236 0.39695 0.61027-0.014631-0.72786z' stroke='%23000' stroke-width='.04pt'/%3E%3Cpath d='m6.9405 1.8923l0.037685-0.69745 0.42314 0.55571c-0.16682-0.05826-0.35276-4.366e-4 -0.46082 0.14174z' stroke='%23000' stroke-linejoin='round' stroke-width='.0375'/%3E%3C/g%3E%3Cpath id='a' d='m6.6959 1.1192c-0.37716 0.17517-0.089012 0.73747 0.27345 0.53362l0.47603-0.24394c0.37716-0.17517 0.089012-0.73747-0.27345-0.53362zm-1.4128 0.72398c-0.37716 0.17517-0.089012 0.73747 0.27345 0.53362l0.47603-0.24394c0.37716-0.17517 0.089012-0.73747-0.27345-0.53362zm-1.4128 0.72398c-0.37716 0.17517-0.089012 0.73747 0.27345 0.53362l0.47603-0.24394c0.37716-0.17517 0.089012-0.73747-0.27345-0.53362zm-1.4128 0.72398c-0.37716 0.17517-0.089012 0.73747 0.27345 0.53362l0.47603-0.24394c0.37716-0.17517 0.089012-0.73747-0.27345-0.53362zm-1.4128 0.72398c-0.37716 0.17517-0.089011 0.73747 0.27345 0.53362l0.47603-0.24394c0.37716-0.17517 0.089011-0.73747-0.27345-0.53362z' color='%23000000' color-rendering='auto' dominant-baseline='auto' fill-rule='evenodd' image-rendering='auto' shape-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3C/g%3E%3Cuse transform='rotate(42.887 -.0038995 4.6444)' width='100%25' height='100%25' xlink:href='%23a'/%3E%3C/svg%3E");
}
.icon-init_angle:before {
content : url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='32' height='32' version='1.1' viewBox='0 0 8.4666664 8.4666664' xmlns='http://www.w3.org/2000/svg'%3E%3Cg transform='translate(0 -288.53)'%3E%3Cpath id='init-angle' d='m3.899 288.76c-0.15258 0-0.27522 0.12318-0.27522 0.27576v0.5187a3.2754 3.2754 0 0 0 -2.6061 2.6066h-0.51925c-0.15258 0-0.27576 0.12266-0.27576 0.27522v0.66807c0 0.15256 0.12318 0.27576 0.27576 0.27576h0.5187a3.2754 3.2754 0 0 0 2.6066 2.6061v0.51924c0 0.1526 0.12264 0.27577 0.27522 0.27577h0.66807c0.15258 0 0.27576-0.12317 0.27576-0.27577v-0.51869a3.2754 3.2754 0 0 0 2.6061 -2.6066h0.51924c0.15258 0 0.27576-0.1232 0.27576-0.27576v-0.66807c0-0.15256-0.12318-0.27522-0.27576-0.27522h-0.5187a3.2754 3.2754 0 0 0 -2.6066 -2.6061v-0.51925c0-0.15258-0.12318-0.27576-0.27576-0.27576zm-0.27522 1.6239v0.58326c0 0.15259 0.12264 0.27577 0.27522 0.27577h0.66807c0.15258 0 0.27576-0.12318 0.27576-0.27577v-0.58216a2.4652 2.4652 0 0 1 1.7755 1.776h-0.58162c-0.15258 0-0.27576 0.12266-0.27576 0.27522v0.66807c0 0.15256 0.12318 0.27576 0.27576 0.27576h0.58162a2.4652 2.4652 0 0 1 -1.7755 1.7772v-0.58327c0-0.15258-0.12318-0.27576-0.27576-0.27576h-0.66807c-0.15258 0-0.27522 0.12318-0.27522 0.27576v0.58217a2.4652 2.4652 0 0 1 -1.7755 -1.776h0.58162c0.15258 0 0.27576-0.1232 0.27576-0.27576v-0.66807c0-0.15256-0.12318-0.27522-0.27576-0.27522h-0.58162a2.4652 2.4652 0 0 1 1.7755 -1.7771zm0.60952 1.6923a0.69412 0.69412 0 0 0 -0.69433 0.69433 0.69412 0.69412 0 0 0 0.69433 0.69433 0.69412 0.69412 0 0 0 0.69433 -0.69433 0.69412 0.69412 0 0 0 -0.69433 -0.69433z' color='%23000000'/%3E%3C/g%3E%3C/svg%3E");
}
.icon-settings:before {
content : url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='32' height='32' version='1.1' viewBox='0 0 8.4666664 8.4666664' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'%3E%3Cg transform='translate(.027095 .27117)'%3E%3Cpath id='a' d='m1.2902 5.73c-0.10703 0-0.19328 0.08625-0.19328 0.19328v1.634c0 0.10703 0.086254 0.19329 0.19328 0.19329h1.4594c0.10703 0 0.19328-0.08626 0.19328-0.19329v-1.634c1.1e-6 -0.10703-0.086254-0.19328-0.19328-0.19328zm-0.86376 0.65387c-0.11707 0-0.2113 0.09424-0.2113 0.2113v0.29717c0 0.11706 0.10103 0.25062 0.2113 0.2113h0.56073v-0.71977zm2.5798 0v0.71977h5.034c0.11707 0 0.2113-0.09424 0.2113-0.2113v-0.29717c0-0.11706-0.094232-0.2113-0.2113-0.2113z' color='%23000000'/%3E%3Cuse transform='matrix(-1 0 0 1 8.4125 -2.7708)' width='100%25' height='100%25' xlink:href='%23a'/%3E%3Cuse transform='translate(0 -5.5562)' width='100%25' height='100%25' xlink:href='%23a'/%3E%3C/g%3E%3C/svg%3E");
}
.icon-calibrations:before {
content : url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='32' height='32' version='1.1' viewBox='0 0 8.4666664 8.4666664' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'%3E%3Cg id='b' transform='rotate(5.5393 2940 107.69)'%3E%3Cg transform='translate(-.13229 .13229)' fill-rule='evenodd' shape-rendering='auto'%3E%3Cpath transform='matrix(.26356 -.023277 .023277 .26356 3.5796 284.51)' d='m15.383 16.422s-6.0845 5.2217-8.939 7.5022c0.69141 0.66747 1.3076 1.4497 1.7344 2.0605l8.9351-7.4963zm-12.402 6.0605l-2.1816 7.916 7.9844-0.60156s0.23427-2.2464-0.99023-3.5664l-0.0058594 0.003906c-0.42184-0.61213-1.0649-1.4393-1.7715-2.1172l0.035156-0.035157c-0.010968 0.008763-0.02232 0.016696-0.033203 0.025391-1.3406-1.3817-3.0371-1.625-3.0371-1.625z' color='%23000000' color-rendering='auto' dominant-baseline='auto' image-rendering='auto' solid-color='%23000000' stroke-width='3.7795' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3C/g%3E%3C/g%3E%3Cuse id='a' transform='rotate(120 4.1795 5.1396)' width='100%25' height='100%25' xlink:href='%23b'/%3E%3Cuse transform='rotate(135 4.189 5.197)' width='100%25' height='100%25' xlink:href='%23a'/%3E%3C/svg%3E");
}
.icon-system:before {
content : url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='32' height='32' version='1.1' viewBox='0 0 8.4666664 8.4666664' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'%3E%3Cg transform='matrix(1.0463 0 0 1.0463 -.33731 -.32381)'%3E%3Crect x='2.1624' y='1.1287' width='4.4416' height='6.3394' rx='.50574' ry='.50574' color='%23000000' fill='none' stroke='%23000' stroke-linecap='round' stroke-linejoin='round' stroke-width='.55844'/%3E%3Cpath id='a' d='m0.73335 1.7654h0.82908v0.80458h-0.82908c-0.19265 0-0.34775-0.13684-0.34775-0.30682v-0.19093c0-0.16998 0.1551-0.30682 0.34775-0.30682z' color='%23000000'/%3E%3Cuse transform='translate(0 1.391)' width='100%25' height='100%25' xlink:href='%23a'/%3E%3Cuse transform='translate(0 2.782)' width='100%25' height='100%25' xlink:href='%23a'/%3E%3Cuse transform='translate(0 4.173)' width='100%25' height='100%25' xlink:href='%23a'/%3E%3Cuse transform='matrix(-1 0 0 1 8.7367 0)' width='100%25' height='100%25' xlink:href='%23a'/%3E%3Cuse transform='matrix(-1 0 0 1 8.7367 1.391)' width='100%25' height='100%25' xlink:href='%23a'/%3E%3Cuse transform='matrix(-1 0 0 1 8.7367 2.782)' width='100%25' height='100%25' xlink:href='%23a'/%3E%3Cuse transform='matrix(-1 0 0 1 8.7367 4.173)' width='100%25' height='100%25' xlink:href='%23a'/%3E%3C/g%3E%3C/svg%3E");
}
.icon-minmax_reset:before {
content : url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='32' height='32' version='1.1' viewBox='0 0 8.4666664 8.4666664' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath d='m7.7156 6.622l-1.4976-2.019-1.4981 2.019h1.0091v1.7258h0.96229v-1.7258zm-7.4936-2.3316v-0.11423c0-0.1108 0.0892-0.2 0.2-0.2h7.6226c0.1108 0 0.2 0.0892 0.2 0.2v0.11423c0 0.1108-0.0892 0.2-0.2 0.2h-7.6226c-0.1108 0-0.2-0.0892-0.2-0.2zm0.52907-2.4458l1.4976 2.019 1.4981-2.019h-1.0091v-1.7258h-0.96229v1.7258z' color='%23000000'/%3E%3C/svg%3E");
}
.icon-audio_on:before {
content : url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='32' height='32' version='1.1' viewBox='0 0 8.4666664 8.4666664' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath d='m4.3851 0.53998c-0.025192 9.5414e-4 -0.049554 0.0094194-0.07028 0.023771l-2.5027 1.6888v-0.12402c0-0.058632-0.047305-0.10594-0.10594-0.10594h-0.72037c-0.058632 0-0.10594 0.047305-0.10594 0.10594v4.2111c0 0.058632 0.047305 0.10594 0.10594 0.10594h0.72037c0.058632 0 0.10594-0.047305 0.10594-0.10594v-0.12247l2.5027 1.6862c0.087879 0.060147 0.20686-0.0025456 0.20671-0.10904v-7.1215c3.296e-4 -0.075029-0.061438-0.13531-0.13643-0.13281z' color='%23000000'/%3E%3Cg transform='translate(.1196 -.037943)' fill='none' stroke='%23000' stroke-linecap='round' stroke-linejoin='round' stroke-width='.44979'%3E%3Cpath d='m5.3045 3.0113c0.69588 0 1.26 0.56412 1.26 1.26-1e-7 0.69588-0.56412 1.26-1.26 1.26' color='%23000000'/%3E%3Cpath d='m5.3045 2.307c1.0848 0 1.9642 0.87942 1.9642 1.9642s-0.87942 1.9642-1.9642 1.9642' color='%23000000'/%3E%3C/g%3E%3C/svg%3E");
}
.icon-audio_off:before {
content: url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='32' height='32' version='1.1' viewBox='0 0 8.4666664 8.4666664' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'%3E%3Cpath d='m4.3851 0.53998c-0.025192 9.5414e-4 -0.049554 0.0094194-0.07028 0.023771l-2.5027 1.6888v-0.12402c0-0.058632-0.047305-0.10594-0.10594-0.10594h-0.72037c-0.058632 0-0.10594 0.047305-0.10594 0.10594v4.2111c0 0.058632 0.047305 0.10594 0.10594 0.10594h0.72037c0.058632 0 0.10594-0.047305 0.10594-0.10594v-0.12247l2.5027 1.6862c0.087879 0.060147 0.20686-0.0025456 0.20671-0.10904v-7.1215c3.296e-4 -0.075029-0.061438-0.13531-0.13643-0.13281z' color='%23000000'/%3E%3Cg transform='matrix(1.2205 0 0 1.2205 -6.4112 -1.9359)'%3E%3Cpath id='a' transform='rotate(-45)' d='m3.7208 9.6335h0.31953c0.058632 0 0.10583 0.047202 0.10583 0.10583v2.5795c0 0.058632-0.047202 0.10583-0.10583 0.10583h-0.31953c-0.058632 0-0.10583-0.047202-0.10583-0.10583v-2.5795c0-0.058632 0.047202-0.10583 0.10583-0.10583z' color='%23000000'/%3E%3Cuse transform='rotate(90 10.543 5.0547)' width='100%25' height='100%25' xlink:href='%23a'/%3E%3C/g%3E%3C/svg%3E");
}
.img-esplogo:before {
content : url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='130' height='64' version='1.1' viewBox='0 0 34.395832 16.933333' xmlns='http://www.w3.org/2000/svg'%3E%3Cg transform='matrix(1.8689 -.028636 .02788 1.9197 .99928 -16.328)' fill='%23d90a00' fill-rule='evenodd' shape-rendering='auto'%3E%3Cpath d='m12.941 16.254l0.30028 0.62408 3.09e-4 0.001054c1.2306-0.34122 2.4616-0.68142 3.6916-1.0223l-0.02627-0.081537z' color='%23000000' color-rendering='auto' dominant-baseline='auto' image-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3Cpath d='m4.4576 15.231c-1.8292 0.009153-4.4496 0.50494-4.4575 1.1929-0.029831 0.52819 5.0065 0.44521 6.4463 0.45673 2.0964-0.004657 4.193 0.020802 6.2893 0.052699l0.20531-0.6796c-3.0033-0.51976-6.1009-1.0346-8.4835-1.0227z' color='%23000000' color-rendering='auto' dominant-baseline='auto' image-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3C/g%3E%3Cg transform='scale(1.1205 .89243)' stroke-width='.39033px' aria-label='ESP '%3E%3Cpath d='m5.7953 8.9439h-2.9427c-1.2253-0.0096171-2.061-1.037-2.0736-2.3938v-5.4229h4.8333v1.54h-3.0596v1.479h2.6327v1.54h-2.6327v0.97582c0 0.49469 0.24226 0.74203 0.72678 0.74203h2.5158z'/%3E%3Cpath d='m9.8864 0.98995c0.84707 0 1.5095 0.13214 1.9872 0.39643l-0.50824 1.4586c-0.68443-0.28001-2.6273-0.67107-2.8388 0.24166-0.088581 0.49698 0.052032 0.69181 0.33326 0.83072 0.21007 0.10503 0.70137 0.26089 1.4739 0.46758 1.2062 0.32189 1.8093 0.99445 1.8093 2.0059s-0.23378 1.5722-0.70136 1.9788c-0.44386 0.38287-1.025 0.57431-1.7433 0.57431h-2.7496v-1.54h2.6022c0.54889 0 0.82334-0.2321 0.82334-0.62598 0-0.39388-0.13214-0.5904-0.39643-0.7361-0.20329-0.11181-0.67086-0.27276-1.4027-0.48283-1.2706-0.36254-1.9059-1.0842-1.9059-2.2363 0.12882-2.1148 2.0339-2.3325 3.2172-2.3328z'/%3E%3Cpath d='m15.096 6.3214v2.6225h-1.7737v-5.55c0-0.71153 0.24057-1.2926 0.7217-1.7433 0.47097-0.44047 1.0707-0.66071 1.961-0.66071 1.4087-0.022185 2.7675 0.89708 2.786 2.5522-0.026916 3.0183-2.3838 2.7694-3.695 2.7793zm0.99536-3.7813c-0.56018 0.0051715-0.89126 0.30569-0.9953 0.90974v1.3926c0.3456 0 0.62513-0.013553 0.83859-0.040659 0.72167-0.094873 1.0825-0.46251 1.062-1.2386-0.020519-0.77609-0.48898-1.0187-0.90527-1.0231z'/%3E%3C/g%3E%3Cg transform='scale(1.0377 .96371)' stroke-width='.11079px' aria-label='Throw-meter'%3E%3Cpath d='m1.0379 9.686h1.9849v0.41978h-0.71406v1.7339h-0.55538v-1.7339h-0.7155z'/%3E%3Cpath d='m4.9096 10.856v0.98381h-0.51932v-0.75012c0.013452-0.3997-0.053854-0.52998-0.24235-0.51499-0.27504 0.039472-0.3384 0.22885-0.34621 0.47027v0.79484h-0.51643v-2.2446h0.51643v0.86553c0.15061-0.19419 0.3221-0.26927 0.53807-0.27553 0.42783 0.031803 0.58439 0.32579 0.56981 0.67078z'/%3E%3Cpath d='m6.5917 10.664c-0.22067-0.10723-0.4241-0.10166-0.57702 0.066361-0.071167 0.084627-0.10675 0.20628-0.10675 0.36496v0.74435h-0.51643v-1.6156h0.51643v0.26543c0.17292-0.27942 0.43551-0.3186 0.68232-0.29284z'/%3E%3Cpath d='m7.6202 10.554c-0.24609 8e-4 -0.33712 0.20328-0.35198 0.47892s0.093432 0.46042 0.35198 0.47893 0.33302-0.20606 0.34766-0.47893-0.10157-0.47972-0.34766-0.47892zm0-0.36929c0.48385 0.01128 0.90441 0.30488 0.88572 0.84822s-0.40179 0.85944-0.88572 0.84822-0.90868-0.30258-0.89004-0.84822 0.40619-0.8595 0.89004-0.84822z'/%3E%3Cpath d='m8.7382 10.224h0.502l0.2712 1.1136 0.27264-1.1136h0.43132l0.2712 1.1021 0.27264-1.1021h0.502l-0.42555 1.6156h-0.56403l-0.27264-1.1108-0.2712 1.1108h-0.56403z'/%3E%3Cpath d='m11.524 10.779h0.90592v0.41978h-0.90592z'/%3E%3Cpath d='m14.338 10.492c0.1384-0.21585 0.33783-0.32657 0.52941-0.30726 0.76615 0.12428 0.56981 0.97355 0.56981 1.6546h-0.51932v-0.84244c0.011002-0.35072-0.087903-0.39817-0.21061-0.42267-0.26278 0.043488-0.30852 0.23057-0.31014 0.47171v0.7934h-0.51932v-0.84244c0.015904-0.28675-0.078871-0.44253-0.21061-0.42267-0.26287 0.043912-0.3035 0.20846-0.31014 0.47027v0.79484h-0.51932v-1.6156h0.51932v0.23658c0.36963-0.4072 0.71932-0.32067 0.98092 0.031741z'/%3E%3Cpath d='m17.535 11.175h-1.2074c0.091709 0.45106 0.73834 0.34873 1.131 0.16878v0.39814c-0.24324 0.099085-0.49452 0.12385-0.73281 0.13992-0.5215-0.012523-0.91864-0.32831-0.92467-0.84821 0.008058-0.59001 0.35873-0.84346 0.89582-0.84822 0.56763 0.026347 0.84571 0.34189 0.83811 0.98959zm-0.53086-0.3188c-0.019014-0.23565-0.12345-0.31473-0.31014-0.32746-0.23027 0.011697-0.32453 0.1231-0.36064 0.32746z'/%3E%3Cpath d='m18.488 9.7653v0.45873h0.5323v0.36929h-0.5323v0.68521c0.005234 0.20077 0.11444 0.20264 0.22215 0.19186h0.26543v0.36929h-0.44286c-0.4131-9.95e-4 -0.55306-0.22127-0.56114-0.56114v-0.68521h-0.25677v-0.36929h0.25677v-0.45873z'/%3E%3Cpath d='m20.951 11.175h-1.2074c0.073212 0.47097 0.60886 0.34209 1.131 0.16878v0.39814c-0.24323 0.099087-0.49453 0.12385-0.73281 0.13992-0.65098-0.005884-0.91864-0.32831-0.92467-0.84821 0.045052-0.57674 0.43888-0.84346 0.89582-0.84822 0.29186 0.017195 0.85632 0.1461 0.83811 0.98959zm-0.53086-0.3188c-0.054242-0.45857-0.66064-0.35701-0.67077 0z'/%3E%3Cpath d='m22.54 10.664c-0.4194-0.10807-0.67161 0.02167-0.68377 0.43132v0.74435h-0.51643v-1.6156h0.51643v0.26543c0.16904-0.27293 0.32097-0.30057 0.68232-0.29284z'/%3E%3C/g%3E%3Cpath d='m28.677 0.8835l-1.4377 1.3714c2.2836 2.7588 2.1977 6.3526-0.2634 8.6395l1.3313 1.4751c3.4492-3.3914 3.5399-8.133 0.3698-11.486zm-2.3125 2.2051l-1.4372 1.3709c1.0984 1.2281 1.0291 3.0265-0.08985 4.0643l1.3302 1.4745c2.0843-2.3087 2.1863-4.8268 0.19685-6.9097zm-2.3944 2.2834l-1.0621 1.0128 1.0441 1.1573c0.55776-0.68429 0.62546-1.5856 0.018-2.1701z' color='%23000000' color-rendering='auto' dominant-baseline='auto' image-rendering='auto' shape-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3C/svg%3E");
}
/* Slider */
.slidecontainer {
  width: 100%;
}
.slider, .slider2 {
  -webkit-appearance: none;
  width: 560px;
  width: -webkit-calc(100% - 340px);
  width:    -moz-calc(100% - 340px);
  width:         calc(100% - 340px);
  height: 10px;
  border-radius: 5px;
  background: #d3d3d3;
  outline: none;
  opacity: 0.8;
  -webkit-transition: .2s;
  transition: opacity .2s;
}
.slider2 {
  width: 450px;
  width: -webkit-calc(100% - 450px);
  width:    -moz-calc(100% - 450px);
  width:         calc(100% - 450px);
}
.slider:hover, .slider2:hover {
  opacity: 1;
}
.slider::-webkit-slider-thumb, .slider2::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 50px;
  height: 50px;
  border: 0;
  background-color: #4c86af;
  background-image: url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='50' height='50' version='1.1' viewBox='0 0 7.9374997 7.9374997' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath d='m1.1251 0.16297h5.6586c0.54893 0 0.99084 0.44192 0.99084 0.99085v5.6586c0 0.54893-0.44192 0.99084-0.99084 0.99084h-5.6586c-0.54893 0-0.99084-0.44192-0.99084-0.99084v-5.6586c0-0.54893 0.44192-0.99085 0.99084-0.99085z' color='%23000000' fill='none' stroke='%23000' stroke-linecap='round' stroke-linejoin='round' stroke-width='.29725'/%3E%3Cpath d='m2.2644 1.612c-0.21897 0.003176-0.39387 0.18332-0.39058 0.40229v3.938c0 0.52858 0.79287 0.52858 0.79287 0v-3.938c0.0033584-0.22355-0.17873-0.40564-0.40229-0.40229zm3.3689 0c-0.21897 0.003176-0.39387 0.18332-0.39058 0.40229v3.938c0 0.52858 0.79287 0.52858 0.79287 0v-3.938c0.0033584-0.22355-0.17873-0.40564-0.40229-0.40229zm-1.6844 0c-0.21897 0.003176-0.39387 0.18332-0.39058 0.40229v3.938c0 0.52858 0.79287 0.52858 0.79287 0v-3.938c0.0033585-0.22355-0.17873-0.40564-0.40229-0.40229z' color='%23000000' color-rendering='auto' dominant-baseline='auto' fill-rule='evenodd' image-rendering='auto' shape-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3C/svg%3E");
  cursor: pointer;
}
.slider::-moz-range-thumb, .slider2::-moz-range-thumb {
  width: 50px;
  height: 50px;
  border: 0;
  background-color: #4c86af;
  background-image: url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='50' height='50' version='1.1' viewBox='0 0 7.9374997 7.9374997' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath d='m1.1251 0.16297h5.6586c0.54893 0 0.99084 0.44192 0.99084 0.99085v5.6586c0 0.54893-0.44192 0.99084-0.99084 0.99084h-5.6586c-0.54893 0-0.99084-0.44192-0.99084-0.99084v-5.6586c0-0.54893 0.44192-0.99085 0.99084-0.99085z' color='%23000000' fill='none' stroke='%23000' stroke-linecap='round' stroke-linejoin='round' stroke-width='.29725'/%3E%3Cpath d='m2.2644 1.612c-0.21897 0.003176-0.39387 0.18332-0.39058 0.40229v3.938c0 0.52858 0.79287 0.52858 0.79287 0v-3.938c0.0033584-0.22355-0.17873-0.40564-0.40229-0.40229zm3.3689 0c-0.21897 0.003176-0.39387 0.18332-0.39058 0.40229v3.938c0 0.52858 0.79287 0.52858 0.79287 0v-3.938c0.0033584-0.22355-0.17873-0.40564-0.40229-0.40229zm-1.6844 0c-0.21897 0.003176-0.39387 0.18332-0.39058 0.40229v3.938c0 0.52858 0.79287 0.52858 0.79287 0v-3.938c0.0033585-0.22355-0.17873-0.40564-0.40229-0.40229z' color='%23000000' color-rendering='auto' dominant-baseline='auto' fill-rule='evenodd' image-rendering='auto' shape-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3C/svg%3E");
  cursor: pointer;
}
/* Checkbox */
.switch {
  position: relative;
  display: inline-block;
  width: 70px;
  height: 34px;
}
.switch input { 
  opacity: 0;
  width: 0;
  height: 0;
}
.slidersw {
  position: absolute;
  cursor: pointer;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: #ccc;
  -webkit-transition: .4s;
  transition: .4s;
}
.slidersw:before {
  position: absolute;
  content: "";
  height: 26px;
  width: 26px;
  left: 4px;
  bottom: 4px;
  background-color: #4c86af;
  -webkit-transition: .4s;
  transition: .4s;
}
input:checked + .slidersw {
  background-color: #ddd;
}
input:focus + .slidersw {
  box-shadow: 0 0 1px #ddd;
}
input:checked + .slidersw:before {
  -webkit-transform: translateX(34px);
  -ms-transform: translateX(34px);
  transform: translateX(34px);
}
/* Rounded checkbox */
.slidersw.round {
  border-radius: 34px;
}
.slidersw.round:before {
  border-radius: 50%;
}
/* Radio */
.radiocontainer {
  display: inline-block;
  position: relative;
  padding: 6px;
  padding-left: 50px;
  margin: 6px;
  cursor: pointer;
  font-size : 1.5em;
  -webkit-user-select: none;
  -moz-user-select: none;
  -ms-user-select: none;
  user-select: none;
}
.radiocontainer input {
  position: absolute;
  opacity: 0;
  cursor: pointer;
}
.checkmark {
  position: absolute;
  top: 0;
  left: 0;
  height: 40px;
  width: 40px;
  background-color: #cdf8fd;
  border-radius: 50%;
}
.radiocontainer input:checked + .checkmark {
  background-color: #4c86af;
}
.checkmark:after {
  content: "";
  position: absolute;
  display: none;
}
.radiocontainer input:checked + .checkmark:after {
  display: block;
}
.radiocontainer .checkmark:after {
 top: 9px;
 left: 9px;
 width: 18px;
 height: 18px;
 border-radius: 50%;
 border: white solid 2px;
 background: black;
}
</style>
<title>ESP Angle meter</title>
</head><body  onload="getSettings(0)">
<div id="header">
<div>
<button class="tabbutton tabmeasurements" type="button" onclick="toggleMeasurements()"><i class="icon-measurements"></i> Data</button>
<button class="tabbutton tabsettings" type="button" onclick="toggleSettings()"><i class="icon-settings"></i> Settings</button>
<button class="tabbutton tabcalibrations" type="button" onclick="toggleCalibrations()"><i class="icon-calibrations"></i> Calibrations</button>
<button class="tabbutton tabsystem" type="button" onclick="toggleSystem()"><i class="icon-system"></i> System</button>
<button class="tabbuttonaudio" type="button" onclick="toggleAudio()"><i class="icon-audio_off" id="audio_off"></i><i class="icon-audio_on" id="audio_on"></i></button>
<div id="battery"><div id="battery-used"></div></div>
</div>
</div>
<div id="settings">
 <div class="slidecontainer">
  <span class="label">Chord:</span><span id="ChordValue">50</span><span class="unit">mm</span>
  <input type="range" min="1" max="200" value="50" class="slider" id="Chord">
 </div>
 <div class="slidecontainer">
  <span class="label">Min:</span><span id="MinLimitValue">50</span><span class="unit">mm</span>
  <input type="range" min="0" max="200" value="25" class="slider" id="MinLimit">
 </div>
 <div class="slidecontainer">
  <span class="label">Max:</span><span id="MaxLimitValue">50</span><span class="unit">mm</span>
  <input type="range" min="0" max="200" value="25" class="slider" id="MaxLimit">
 </div>
 <div class="buttons">
  <button class="button button2" type="button" onclick="getSettings(1)">Load</button>
  <button class="button button2" type="button" onclick="sendData(301)">Save</button>
  <span class="label5">Rot. angle: </span>
  <label class="radiocontainer">X axis<input type="radio" id="X" checked="checked" name="axis"><span class="checkmark"></span></label>
  <label class="radiocontainer">Y axis<input type="radio" id="Y" checked="none" name="axis"><span class="checkmark"></span></label>
  <label class="radiocontainer">Z axis<input type="radio" id="Z" checked="none" name="axis"><span class="checkmark"></span></label>
 </div>
</div>
<div id="calibrations">
 <div class="slidecontainer">
  <span class="label4">X(g):</span><span id="XValue">0</span>
  <span id="XOffsetValue">0</span><input type="range" min="-300" max="300" value="0" class="slider2" id="XOffset">
 </div>
 <div class="slidecontainer">
  <span class="label4">Y(g):</span><span id="YValue">0</span>
  <span id="YOffsetValue">0</span><input type="range" min="-300" max="300" value="0" class="slider2" id="YOffset">
 </div>
 <div class="slidecontainer">
  <span class="label4">Z(g):</span><span id="ZValue">0</span>
  <span id="ZOffsetValue">0</span><input type="range" min="-300" max="300" value="0" class="slider2" id="ZOffset">
 </div>
 <div class="buttons">
  <button class="button button2" type="button" onclick="getSettings(2)">Load</button>
  <button class="button button2" type="button" onclick="sendData(305)">Save</button>
 </div>
</div>
<div id="measurements">
<div id="master">
<div class="values">
<span class="label">Angle:</span><span id="AngleValue">0.00</span><span class="unit">deg</span><br>
<span class="label">Throw:</span><span id="ThrowValue">0</span><span class="unit">mm</span>
<label class="switch"><input type="checkbox" id="sensor1" onclick="invertAngle(1)"><span class="slidersw round"></span></label>
</div>
<div class="values">
<span class="label2">Max:</span><span id="MaxThrowValue">0</span><span class="unit">mm</span><br>
<span class="label2">Min:</span><span id="MinThrowValue">0</span><span class="unit">mm</span>
</div>
<div class="buttons">
<button class="button" type="button" onclick="sendData(304)"><i class="icon-init_angle"></i> Angle</button><br>
<button class="button" type="button" onclick="sendData(303)"><i class="icon-minmax_reset"></i> Min/Max</button>
</div>
</div>
<div id="slave">
<hr class="separator"><br>
<div class="values">
<span class="label">Angle2:</span><span id="AngleValue2">0.00</span><span class="unit">deg</span><br>
<span class="label">Throw2:</span><span id="ThrowValue2">0</span><span class="unit">mm</span>
<label class="switch"><input type="checkbox" id="sensor2" onclick="invertAngle(2)"><span class="slidersw round"></span></label>
</div>
<div class="values">
<span class="label2">Max2:</span><span id="MaxThrowValue2">0</span><span class="unit">mm</span><br>
<span class="label2">Min2:</span><span id="MinThrowValue2">0</span><span class="unit">mm</span>
</div>
<div class="buttons">
<span class="label3">Differential</span><br><span id="DiffValue">0</span><span class="unit">%</span>
</div>
</div>
</div>
<div id="system">
<p id="sysdata"></p>
<a href="http://debat.local/update"><button class="button button2" type="button">Update FW</button></a>
<a href="http://debat.local/wifi"><button class="button button2" type="button">Wifi config</button></a>
</div>
<div id="bottom"><a href="http://github.com/f5soh/aeromodeling-throw-meter"><i class="img-esplogo"></i></a></div>
<script>
var canPlay=false;
var audioEnabled=false;
var AudioAPI=null;
window.addEventListener('load', checkAudioApi, false);
document.getElementById("audio_off").style.display = "block";
document.getElementById("audio_on").style.display = "none";

function checkAudioApi(){ 
 if(self.AudioContext){AudioAPI=self.AudioContext;canPlay=true;return;}
 else if (self.webkitAudioContext){AudioAPI=self.webkitAudioContext;canPlay=true;return;}
 else{canPlay=false;return;}
}

function beep(vol, freq, duration){
  if (!canPlay || !audioEnabled){return;}
  this.a=new AudioAPI();v=a.createOscillator();u=a.createGain();v.connect(u);v.frequency.value=freq;v.type="square";
  u.connect(a.destination);u.gain.value=vol*0.01;v.start(a.currentTime);v.stop(a.currentTime+duration*0.001);
}
function toggleAudio() {
  if (canPlay && !audioEnabled) {
    document.getElementById("audio_on").style.display = "block";document.getElementById("audio_off").style.display = "none";audioEnabled = true;
  } else {
    document.getElementById("audio_off").style.display = "block";document.getElementById("audio_on").style.display = "none";audioEnabled = false;
  }
  beep(20, 200, 25);
}
var slave_found = false;
document.getElementById("system").style.display = "none";
document.getElementById("calibrations").style.display = "none";
document.getElementById("settings").style.display = "none";
document.getElementById("measurements").style.display = "block";
document.getElementById("slave").style.display = "none";
var chord_slider = document.getElementById("Chord");
var chord_display = document.getElementById("ChordValue");
var min_slider = document.getElementById("MinLimit");
var min_display = document.getElementById("MinLimitValue");
var max_slider = document.getElementById("MaxLimit");
var max_display = document.getElementById("MaxLimitValue");

var xoffset_slider = document.getElementById("XOffset");
var xoffset_display = document.getElementById("XOffsetValue");
var yoffset_slider = document.getElementById("YOffset");
var yoffset_display = document.getElementById("YOffsetValue");
var zoffset_slider = document.getElementById("ZOffset");
var zoffset_display = document.getElementById("ZOffsetValue");

xoffset_slider.oninput = function() {xoffset_display.innerHTML = (this.value / 10000).toFixed(4);}
yoffset_slider.oninput = function() {yoffset_display.innerHTML = (this.value / 10000).toFixed(4);}
zoffset_slider.oninput = function() {zoffset_display.innerHTML = (this.value / 10000).toFixed(4);}

chord_slider.oninput = function() {chord_display.innerHTML = this.value;}
min_slider.oninput = function() {min_display.innerHTML = this.value;}
max_slider.oninput = function() {max_display.innerHTML = this.value;}

function toggleSettings() {
 if (document.getElementById("settings").style.display == "none") {
  document.getElementById("settings").style.display = "block";
  document.getElementById("measurements").style.display = "none";
  document.getElementById("calibrations").style.display = "none";
  document.getElementById("system").style.display = "none";
 }
}
function toggleCalibrations() {
 if (document.getElementById("calibrations").style.display == "none") {
  document.getElementById("calibrations").style.display = "block";
  document.getElementById("settings").style.display = "none";
  document.getElementById("measurements").style.display = "none";
  document.getElementById("system").style.display = "none";
 }
}
function toggleSystem() {
 if (document.getElementById("system").style.display == "none") {
  document.getElementById("system").style.display = "block";
  document.getElementById("calibrations").style.display = "none";
  document.getElementById("settings").style.display = "none";
  document.getElementById("measurements").style.display = "none";
 }
 getSysData();
}
function toggleMeasurements() {
 if (document.getElementById("measurements").style.display == "none") {
  document.getElementById("measurements").style.display = "block";
  document.getElementById("settings").style.display = "none";
  document.getElementById("calibrations").style.display = "none";
  document.getElementById("system").style.display = "none";
 } 
 sendData(0);
}
function invertAngle(sensor){
var checkBox1 = document.getElementById("sensor1");
var checkBox2 = document.getElementById("sensor2");
if (sensor == 1) {
 if (checkBox1.checked == true){sendData(201);} else {sendData(200);}
} else if (sensor == 2) {
 if (checkBox2.checked == true){sendData(203);} else {sendData(202);}
}
};

function sendData(value) {
var axisChecked = 0;
if (Y.checked) {axisChecked = 1;} else if (Z.checked) {axisChecked = 2;}
const xhttpcmd = new XMLHttpRequest();
xhttpcmd.open("GET", "setData?cmd=" + value + "&chord="+ chord_slider.value + "&min=" + min_slider.value + "&max=" + max_slider.value + "&xoff=" + xoffset_slider.value + "&yoff=" + yoffset_slider.value + "&zoff=" + zoffset_slider.value + "&axis=" + axisChecked, true);
xhttpcmd.send(null);
beep(20, 180, 25); 
}

setInterval(function() {
// Call a function repetatively
getData();
checkLimits();
}, 300); //300ms update rate

function checkLimits() {
var throw_value = parseFloat(document.getElementById("ThrowValue").innerHTML);
var throw_value2 = parseFloat(document.getElementById("ThrowValue2").innerHTML);
var min_limit = parseFloat(min_slider.value);
var max_limit = parseFloat(max_slider.value);
 if (throw_value > max_limit) {
  document.getElementById("ThrowValue").style.color = 'red';
  document.getElementById("MinThrowValue").style.color = 'black';
  document.getElementById("MaxThrowValue").style.color = 'red';
  beep(30, 120, 150);
 } else if (throw_value < -min_limit) {
  document.getElementById("ThrowValue").style.color = 'red';
  document.getElementById("MinThrowValue").style.color = 'red';
  document.getElementById("MaxThrowValue").style.color = 'black';
  beep(30, 110, 150);
 } else {
  document.getElementById("ThrowValue").style.color = 'black';
  document.getElementById("MinThrowValue").style.color = 'black';
  document.getElementById("MaxThrowValue").style.color = 'black';
 }
 if (slave_found && (throw_value2 > max_limit)) {
  document.getElementById("ThrowValue2").style.color = 'red';
  document.getElementById("MinThrowValue2").style.color = 'black';
  document.getElementById("MaxThrowValue2").style.color = 'red';
  beep(30, 120, 150);
 } else if (slave_found && (throw_value2 < -min_limit)) {
  document.getElementById("ThrowValue2").style.color = 'red';
  document.getElementById("MinThrowValue2").style.color = 'red';
  document.getElementById("MaxThrowValue2").style.color = 'black';
  beep(30, 110, 150);
 } else {
  document.getElementById("ThrowValue2").style.color = 'black';
  document.getElementById("MinThrowValue2").style.color = 'black';
  document.getElementById("MaxThrowValue2").style.color = 'black';
 }
 if (slave_found) {
  var diff = 0;
  throw_value = Math.abs(throw_value);
  throw_value2 = Math.abs(throw_value2);
  // Calc error/differential
  if (throw_value > throw_value2 + 0.1) {
     diff = 100 - ((throw_value2 * 100) / throw_value);
  } else if (throw_value < throw_value2 - 0.1){
     diff = 100 - ((throw_value * 100) / throw_value2);
  }
  document.getElementById("DiffValue").innerHTML = diff.toFixed(0);
 }
}

function getData() {
const xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function(event) {
 if (this.readyState === XMLHttpRequest.DONE && this.status === 200) {
  var str_in = this.responseText;
  var words = str_in.split(':');
  //document.getElementById("Chord").innerHTML = words[0];
  document.getElementById("AngleValue").innerHTML = words[1];
  document.getElementById("ThrowValue").innerHTML = words[2];
  document.getElementById("MinThrowValue").innerHTML = words[3];
  document.getElementById("MaxThrowValue").innerHTML = words[4];
  // Slave device
  document.getElementById("AngleValue2").innerHTML = words[5];
  document.getElementById("ThrowValue2").innerHTML = words[6];
  document.getElementById("MinThrowValue2").innerHTML = words[7];
  document.getElementById("MaxThrowValue2").innerHTML = words[8];
  if ((words[9] == "0") && slave_found) {
    slave_found = false;
    document.getElementById("slave").style.display = "none";
  } else if ((words[9] == "1") && !slave_found) {
    slave_found = true;
    document.getElementById("slave").style.display = "block"; 
  }
  document.getElementById("XValue").innerHTML = words[10];
  document.getElementById("YValue").innerHTML = words[11];
  document.getElementById("ZValue").innerHTML = words[12];
  document.getElementById("battery-used").style.height = words[13] + "%";
  var battery_used = parseInt(words[13]);
  if (battery_used > 90) {
    document.getElementById("battery").style.backgroundColor = "red";
    if (battery_used > 95) {document.getElementById("battery-used").style.height = "90%";alert("Please charge battery!!!!");}
  } else if (battery_used > 70) {
    document.getElementById("battery").style.backgroundColor = "orange";
  } else if (battery_used > 20) {
    document.getElementById("battery").style.backgroundColor = "#66b000";
  } else {
    document.getElementById("battery").style.backgroundColor = "#66cd00";
  }
 }
};
xhttp.open("GET", "readData", true);
xhttp.send(null);
}

function getSettings(state) {
const xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function(event) {
 if (this.readyState === XMLHttpRequest.DONE && this.status === 200) {
  var str_in = this.responseText;
  var words = str_in.split(':');
  if ((state == 0) || (state == 1)) {
    document.getElementById("ChordValue").innerHTML = words[0];
    chord_slider.value = words[0];
    document.getElementById("MinLimitValue").innerHTML = words[1];
    min_slider.value = words[1];
    document.getElementById("MaxLimitValue").innerHTML = words[2];
    max_slider.value = words[2];
    if (words[3] == "0") {
      document.getElementById("X").checked = "true";
    } else if (words[3] == "1") {
      document.getElementById("Y").checked = "true"; 
    } else if (words[3] == "2") {
      document.getElementById("Z").checked = "true";
    }
  }
  if ((state == 0) || (state == 2)) {
    document.getElementById("XOffsetValue").innerHTML = (parseFloat(words[4]) / 10000).toFixed(4);
    document.getElementById("YOffsetValue").innerHTML = (parseFloat(words[5]) / 10000).toFixed(4);
    document.getElementById("ZOffsetValue").innerHTML = (parseFloat(words[6]) / 10000).toFixed(4);
    xoffset_slider.value = words[4];
    yoffset_slider.value = words[5];
    zoffset_slider.value = words[6];
  } 
 }
};
xhttp.open("GET", "readSettings", true);
xhttp.send(null);
beep(20, 180, 25);
}

function getSysData() {
const xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function(event) {
 if (this.readyState === XMLHttpRequest.DONE && this.status === 200) {
  var str_in = this.responseText;
  var words = str_in.split(':');
  var sys_content = "<b>Free memory:</b> " + words[0] + " bytes</b>";
  sys_content += "<br><b>SDK/Arduino version:</b> " + words[1] + "/" + words[2];
  sys_content += "<br><b>FW version:</b> Wifi_Angle_meter_mma8452_esp01_" + words[3] + ".bin";
  sys_content += "<br><b>ESP voltage:</b> "+ words[4] + "V";
  document.getElementById("sysdata").innerHTML = sys_content;
 }
};
xhttp.open("GET", "readSysData", true);
xhttp.send(null);
}
</script>
</body></html>
)=====";
