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
#settings {
margin-left : 2px;
margin-right : 2px;
padding : 15px;
border : black solid 2px;
background-color : #f4e969;
display : none;
}
#measurements {
padding : 10px 0 0 15px;
border : black solid 2px;
background-color : #6adbe8;
}
#chord {
display : inline-block;
}
#minmax {
display : inline-block;
}
#ChordValue, #AngleValue, #MinLimitValue, #MaxLimitValue, #ThrowValue, #MinThrowValue, #MaxThrowValue, #AngleValue2, #ThrowValue2, #MinThrowValue2, #MaxThrowValue2, #DiffValue {
text-align : right;
display : inline-block;
font : bold 2em sans-serif;
margin : 8px;
border-radius : 8px;
padding : 8px 8px;
background-color : #cdf8fd;
width : 140px;
}
#ChordValue, #MinLimitValue, #MaxLimitValue, #ThrowValue, #MinThrowValue, #MaxThrowValue, #ThrowValue2, #MinThrowValue2, #MaxThrowValue2, #DiffValue {
width : 100px;
}
.buttons {
display : inline-block;
vertical-align : top;
}
.values {
display : inline-block;
white-space : nowrap;
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
margin : 6px 6px -2px 6px;
border-radius : 20px 20px 0 0;
width : 20%;
cursor : pointer;
}
.tabmeasurements {
background-color : #6adbe8;
margin : 6px 6px -6px 6px;
border-bottom : 4px solid #6adbe8;
}
.tabsettings {
background-color : #f4e969;
margin : 6px 6px -6px 6px;
border-bottom : 4px solid #f4e969;
}
.label, .label2, .label3 {
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
.icon-measurements, .icon-init_angle, .icon-minmax_reset, .icon-settings, .img-esplogo {
display : inline-block;
vertical-align : -30%;
background-color : transparent;
}
.icon-measurements:before {
content : url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='32' height='32' version='1.1' viewBox='0 0 8.4666664 8.4666664' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath d='m0.60742 4.4805a0.30003 0.30003 0 1 0 0 0.59961h7.4141a0.30003 0.30003 0 1 0 0 -0.59961z' color='%23000000' color-rendering='auto' dominant-baseline='auto' fill-rule='evenodd' image-rendering='auto' shape-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3Cg transform='matrix(.93154 .11113 -.094608 .79304 1.1201 .015298)' fill-rule='evenodd'%3E%3Cpath d='m7.0664 1.3066l-0.095703 0.029297 0.83008 2.7012 0.095703-0.029297z' color='%23000000' color-rendering='auto' dominant-baseline='auto' image-rendering='auto' shape-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3Cpath d='m7.7311 3.6396l-0.24996-0.13236 0.39695 0.61027-0.014631-0.72786z' stroke='%23000' stroke-width='.04pt'/%3E%3Cpath d='m6.9405 1.8923l0.037685-0.69745 0.42314 0.55571c-0.16682-0.05826-0.35276-4.366e-4 -0.46082 0.14174z' stroke='%23000' stroke-linejoin='round' stroke-width='.0375'/%3E%3C/g%3E%3Cpath d='m6.6959 1.1192c-0.37716 0.17517-0.089012 0.73747 0.27345 0.53362l0.47603-0.24394c0.37716-0.17517 0.089012-0.73747-0.27345-0.53362zm-1.4128 0.72398c-0.37716 0.17517-0.089012 0.73747 0.27345 0.53362l0.47603-0.24394c0.37716-0.17517 0.089012-0.73747-0.27345-0.53362zm-1.4128 0.72398c-0.37716 0.17517-0.089012 0.73747 0.27345 0.53362l0.47603-0.24394c0.37716-0.17517 0.089012-0.73747-0.27345-0.53362zm-1.4128 0.72398c-0.37716 0.17517-0.089012 0.73747 0.27345 0.53362l0.47603-0.24394c0.37716-0.17517 0.089012-0.73747-0.27345-0.53362zm-1.4128 0.72398c-0.37716 0.17517-0.089011 0.73747 0.27345 0.53362l0.47603-0.24394c0.37716-0.17517 0.089011-0.73747-0.27345-0.53362z' color='%23000000' color-rendering='auto' dominant-baseline='auto' fill-rule='evenodd' image-rendering='auto' shape-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3Cpath d='m7.2615 6.9372c-0.40774-0.081726-0.25966-0.69596 0.14053-0.58291l0.52 0.12536c0.40774 0.081726 0.25966 0.69596-0.14053 0.58291zm-1.5433-0.37206c-0.40774-0.081726-0.25966-0.69596 0.14053-0.58291l0.52 0.12536c0.40774 0.081726 0.25966 0.69596-0.14053 0.58291zm-1.5433-0.37206c-0.40774-0.081726-0.25966-0.69596 0.14053-0.58291l0.52 0.12536c0.40774 0.081726 0.25966 0.69596-0.14053 0.58291zm-1.5433-0.37206c-0.40774-0.081726-0.25966-0.69596 0.14053-0.58291l0.52 0.12536c0.40774 0.081726 0.25966 0.69596-0.14053 0.58291zm-1.5433-0.37206c-0.40774-0.081726-0.25966-0.69596 0.14053-0.58291l0.52 0.12536c0.40774 0.081726 0.25966 0.69596-0.14053 0.58291z' color='%23000000' color-rendering='auto' dominant-baseline='auto' fill-rule='evenodd' image-rendering='auto' shape-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3C/svg%3E");
}
.icon-init_angle:before {
content : url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='32' height='32' version='1.1' viewBox='0 0 8.4666664 8.4666664' xmlns='http://www.w3.org/2000/svg'%3E%3Cg transform='translate(0 -288.53)'%3E%3Cpath id='init-angle' d='m3.899 288.76c-0.15258 0-0.27522 0.12318-0.27522 0.27576v0.5187a3.2754 3.2754 0 0 0 -2.6061 2.6066h-0.51925c-0.15258 0-0.27576 0.12266-0.27576 0.27522v0.66807c0 0.15256 0.12318 0.27576 0.27576 0.27576h0.5187a3.2754 3.2754 0 0 0 2.6066 2.6061v0.51924c0 0.1526 0.12264 0.27577 0.27522 0.27577h0.66807c0.15258 0 0.27576-0.12317 0.27576-0.27577v-0.51869a3.2754 3.2754 0 0 0 2.6061 -2.6066h0.51924c0.15258 0 0.27576-0.1232 0.27576-0.27576v-0.66807c0-0.15256-0.12318-0.27522-0.27576-0.27522h-0.5187a3.2754 3.2754 0 0 0 -2.6066 -2.6061v-0.51925c0-0.15258-0.12318-0.27576-0.27576-0.27576zm-0.27522 1.6239v0.58326c0 0.15259 0.12264 0.27577 0.27522 0.27577h0.66807c0.15258 0 0.27576-0.12318 0.27576-0.27577v-0.58216a2.4652 2.4652 0 0 1 1.7755 1.776h-0.58162c-0.15258 0-0.27576 0.12266-0.27576 0.27522v0.66807c0 0.15256 0.12318 0.27576 0.27576 0.27576h0.58162a2.4652 2.4652 0 0 1 -1.7755 1.7772v-0.58327c0-0.15258-0.12318-0.27576-0.27576-0.27576h-0.66807c-0.15258 0-0.27522 0.12318-0.27522 0.27576v0.58217a2.4652 2.4652 0 0 1 -1.7755 -1.776h0.58162c0.15258 0 0.27576-0.1232 0.27576-0.27576v-0.66807c0-0.15256-0.12318-0.27522-0.27576-0.27522h-0.58162a2.4652 2.4652 0 0 1 1.7755 -1.7771zm0.60952 1.6923a0.69412 0.69412 0 0 0 -0.69433 0.69433 0.69412 0.69412 0 0 0 0.69433 0.69433 0.69412 0.69412 0 0 0 0.69433 -0.69433 0.69412 0.69412 0 0 0 -0.69433 -0.69433z' color='%23000000'/%3E%3C/g%3E%3C/svg%3E");
}
.icon-settings:before {
content : url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='32' height='32' version='1.1' viewBox='0 0 8.4666664 8.4666664' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'%3E%3Cg transform='translate(.027095 .27117)'%3E%3Cpath id='a' d='m1.2902 5.73c-0.10703 0-0.19328 0.08625-0.19328 0.19328v1.634c0 0.10703 0.086254 0.19329 0.19328 0.19329h1.4594c0.10703 0 0.19328-0.08626 0.19328-0.19329v-1.634c1.1e-6 -0.10703-0.086254-0.19328-0.19328-0.19328zm-0.86376 0.65387c-0.11707 0-0.2113 0.09424-0.2113 0.2113v0.29717c0 0.11706 0.10103 0.25062 0.2113 0.2113h0.56073v-0.71977zm2.5798 0v0.71977h5.034c0.11707 0 0.2113-0.09424 0.2113-0.2113v-0.29717c0-0.11706-0.094232-0.2113-0.2113-0.2113z' color='%23000000'/%3E%3Cuse transform='matrix(-1 0 0 1 8.4125 -2.7708)' width='100%25' height='100%25' xlink:href='%23a'/%3E%3Cuse transform='translate(0 -5.5562)' width='100%25' height='100%25' xlink:href='%23a'/%3E%3C/g%3E%3C/svg%3E");
}
.icon-chord_settings:before {
content : url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='32' height='32' version='1.1' viewBox='0 0 8.4666664 8.4666664' xmlns='http://www.w3.org/2000/svg'%3E%3Cg transform='translate(.26458 -288.53)'%3E%3Cpath transform='matrix(.26458 0 0 .26458 0 288.53)' d='m7.2031 10.129l-7.6309 5.6602 7.6309 5.6621v-3.8141h15.523v3.8141l7.6309-5.6621-7.6309-5.6602v3.8712h-15.523z' color='%23000000' color-rendering='auto' dominant-baseline='auto' fill-rule='evenodd' image-rendering='auto' shape-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3C/g%3E%3C/svg%3E");
}
.icon-minmax_reset:before {
content : url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='32' height='32' version='1.1' viewBox='0 0 8.4666664 8.4666664' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath d='m7.7156 6.622l-1.4976-2.019-1.4981 2.019h1.0091v1.7258h0.96229v-1.7258zm-7.4936-2.3316v-0.11423c0-0.1108 0.0892-0.2 0.2-0.2h7.6226c0.1108 0 0.2 0.0892 0.2 0.2v0.11423c0 0.1108-0.0892 0.2-0.2 0.2h-7.6226c-0.1108 0-0.2-0.0892-0.2-0.2zm0.52907-2.4458l1.4976 2.019 1.4981-2.019h-1.0091v-1.7258h-0.96229v1.7258z' color='%23000000'/%3E%3C/svg%3E");
}
.img-esplogo:before {
content : url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='130' height='64' version='1.1' viewBox='0 0 34.395832 16.933333' xmlns='http://www.w3.org/2000/svg'%3E%3Cg%3E%3Cg transform='matrix(1.8689 -.028636 .02788 1.9197 .99928 -16.328)' fill='%23d90a00' fill-rule='evenodd' shape-rendering='auto'%3E%3Cpath d='m12.941 16.254l0.30028 0.62408 3.09e-4 0.001054c1.2306-0.34122 2.4616-0.68142 3.6916-1.0223l-0.02627-0.081537z' color='%23000000' color-rendering='auto' dominant-baseline='auto' image-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3Cpath d='m4.4576 15.231c-1.8292 0.009153-4.4496 0.50494-4.4575 1.1929-0.029831 0.52819 5.0065 0.44521 6.4463 0.45673 2.0964-0.004657 4.193 0.020802 6.2893 0.052699l0.20531-0.6796c-3.0033-0.51976-6.1009-1.0346-8.4835-1.0227z' color='%23000000' color-rendering='auto' dominant-baseline='auto' image-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3C/g%3E%3Cg%3E%3Cg transform='scale(1.1205 .89243)' stroke-width='.39033px' aria-label='ESP '%3E%3Cpath d='m5.7953 8.9439h-2.9427q-0.99106 0-1.54-0.66071-0.53365-0.6353-0.53365-1.7331v-5.4229h4.8333v1.54h-3.0596v1.479h2.6327v1.54h-2.6327v0.97582q0 0.74203 0.72678 0.74203h2.5158z'/%3E%3Cpath d='m12.143 6.6873q0 1.0724-0.70137 1.6823-0.66579 0.57431-1.7433 0.57431h-2.7496v-1.54h2.6022q0.82334 0 0.82334-0.69629v-0.076236q0-0.37101-0.39643-0.58956-0.30494-0.16772-1.4027-0.48283-1.9059-0.54381-1.9059-2.1651v-0.14231q0-0.9809 0.74711-1.6365 0.71661-0.62513 1.7331-0.62513h0.73694q1.2706 0 1.9872 0.39643l-0.50824 1.4586q-0.55398-0.30494-1.4281-0.30494h-0.70645q-0.35068 0-0.57431 0.22362-0.21854 0.21854-0.21854 0.50824v0.060988q0 0.3761 0.42184 0.58447 0.31511 0.15755 1.4739 0.46758 1.8093 0.48283 1.8093 2.0177z'/%3E%3Cpath d='m18.791 3.6125q0 1.235-0.6912 1.8805-0.88942 0.82843-3.0037 0.82843v2.6225h-1.7737v-5.55q0-1.0673 0.7217-1.7433 0.70645-0.66071 1.7992-0.66071h0.2897q1.1435 0 1.8805 0.6353 0.7776 0.66071 0.7776 1.7483zm-1.7737 0.0864v-0.21854q0-0.38626-0.19313-0.64038-0.22871-0.29986-0.64546-0.29986h-0.18805q-0.39643 0-0.64546 0.26428-0.24904 0.26428-0.24904 0.64546v1.3926q0.5184 0 0.83859-0.040659 1.0825-0.14231 1.0825-1.1029z'/%3E%3C/g%3E%3Cg transform='scale(1.0377 .96371)' stroke-width='.11079px' aria-label='Throw-meter'%3E%3Cpath d='m1.0379 9.686h1.9849v0.41978h-0.71406v1.7339h-0.55538v-1.7339h-0.7155z'/%3E%3Cpath d='m4.9096 10.856v0.98381h-0.51932v-0.75012q0-0.21205-0.010098-0.29139-0.0086552-0.07934-0.031736-0.11685-0.030293-0.050489-0.082225-0.077898-0.051932-0.02885-0.11829-0.02885-0.16156 0-0.25389 0.1255-0.092323 0.12406-0.092323 0.34477v0.79484h-0.51643v-2.2446h0.51643v0.86553q0.11685-0.14137 0.24812-0.20773 0.13127-0.0678 0.28995-0.0678 0.27985 0 0.42411 0.17166 0.1457 0.17166 0.1457 0.49912z'/%3E%3Cpath d='m6.5917 10.664q-0.0678-0.031736-0.1356-0.046161-0.066357-0.015868-0.13416-0.015868-0.19907 0-0.30726 0.12839-0.10675 0.12694-0.10675 0.36496v0.74435h-0.51643v-1.6156h0.51643v0.26543q0.099535-0.15868 0.22792-0.23081 0.12983-0.07357 0.31015-0.07357 0.025966 0 0.056259 0.002885 0.030293 0.001443 0.087995 0.008656z'/%3E%3Cpath d='m7.6202 10.554q-0.17166 0-0.26254 0.12406-0.089438 0.12262-0.089438 0.35486t0.089438 0.35631q0.09088 0.12262 0.26254 0.12262 0.16878 0 0.25822-0.12262 0.089438-0.12406 0.089438-0.35631t-0.089438-0.35486q-0.089438-0.12406-0.25822-0.12406zm0-0.36929q0.41689 0 0.65059 0.22504 0.23513 0.22504 0.23513 0.62318 0 0.39814-0.23513 0.62318-0.23369 0.22504-0.65059 0.22504-0.41834 0-0.65491-0.22504-0.23513-0.22504-0.23513-0.62318 0-0.39814 0.23513-0.62318 0.23658-0.22504 0.65491-0.22504z'/%3E%3Cpath d='m8.7382 10.224h0.502l0.2712 1.1136 0.27264-1.1136h0.43132l0.2712 1.1021 0.27264-1.1021h0.502l-0.42555 1.6156h-0.56403l-0.27264-1.1108-0.2712 1.1108h-0.56403z'/%3E%3Cpath d='m11.524 10.779h0.90592v0.41978h-0.90592z'/%3E%3Cpath d='m14.338 10.492q0.098093-0.15002 0.23225-0.22792 0.1356-0.07934 0.29716-0.07934 0.27841 0 0.42411 0.17166 0.1457 0.17166 0.1457 0.49912v0.98381h-0.51932v-0.84244q0.001442-0.018753 0.001442-0.038948 0.001443-0.020196 0.001443-0.057702 0-0.17166-0.050489-0.24812-0.050489-0.077897-0.16301-0.077897-0.14714 0-0.22792 0.12117-0.07934 0.12117-0.082225 0.35054v0.7934h-0.51932v-0.84244q0-0.26831-0.046161-0.34477-0.046162-0.077897-0.16445-0.077897-0.14858 0-0.22936 0.12262-0.080783 0.12117-0.080783 0.34765v0.79484h-0.51932v-1.6156h0.51932v0.23658q0.095208-0.13704 0.21782-0.20628 0.12406-0.069242 0.27264-0.069242 0.16734 0 0.29572 0.080783 0.12839 0.080782 0.19474 0.22648z'/%3E%3Cpath d='m17.535 11.028v0.14714h-1.2074q0.018753 0.18176 0.13127 0.27264 0.11252 0.090881 0.31447 0.090881 0.16301 0 0.33323-0.047604 0.17166-0.049047 0.35198-0.14714v0.39814q-0.1832 0.069242-0.36641 0.10386-0.1832 0.036063-0.3664 0.036063-0.43853 0-0.68232-0.22215-0.24235-0.22359-0.24235-0.62606 0-0.39526 0.23802-0.62174 0.23946-0.22648 0.6578-0.22648 0.38083 0 0.60875 0.22936 0.22936 0.22936 0.22936 0.61308zm-0.53086-0.17166q0-0.14714-0.086552-0.23658-0.08511-0.09088-0.22359-0.09088-0.15002 0-0.24379 0.08511-0.093765 0.083668-0.11685 0.24235z'/%3E%3Cpath d='m18.488 9.7653v0.45873h0.5323v0.36929h-0.5323v0.68521q0 0.11252 0.044719 0.15291 0.044719 0.038949 0.17743 0.038949h0.26543v0.36929h-0.44286q-0.30582 0-0.4342-0.12694-0.12694-0.12839-0.12694-0.4342v-0.68521h-0.25677v-0.36929h0.25677v-0.45873z'/%3E%3Cpath d='m20.951 11.028v0.14714h-1.2074q0.018753 0.18176 0.13127 0.27264 0.11252 0.090881 0.31447 0.090881 0.16301 0 0.33323-0.047604 0.17166-0.049047 0.35198-0.14714v0.39814q-0.1832 0.069242-0.3664 0.10386-0.1832 0.036063-0.36641 0.036063-0.43853 0-0.68232-0.22215-0.24235-0.22359-0.24235-0.62606 0-0.39526 0.23802-0.62174 0.23946-0.22648 0.6578-0.22648 0.38083 0 0.60875 0.22936 0.22936 0.22936 0.22936 0.61308zm-0.53086-0.17166q0-0.14714-0.086552-0.23658-0.08511-0.09088-0.22359-0.09088-0.15002 0-0.24379 0.08511-0.093765 0.083668-0.11684 0.24235z'/%3E%3Cpath d='m22.54 10.664q-0.0678-0.031736-0.1356-0.046161-0.066357-0.015868-0.13416-0.015868-0.19907 0-0.30726 0.12839-0.10675 0.12694-0.10675 0.36496v0.74435h-0.51643v-1.6156h0.51643v0.26543q0.099535-0.15868 0.22792-0.23081 0.12983-0.07357 0.31015-0.07357 0.025966 0 0.056259 0.002885 0.030293 0.001443 0.087995 0.008656z'/%3E%3C/g%3E%3Cpath d='m30.944 6.7293c0.079599-2.2605-0.79863-4.3384-2.2669-5.8458l-1.4377 1.3714c1.107 1.1281 1.7662 2.6916 1.7059 4.4041-0.059587 1.6922-0.80954 3.1895-1.9693 4.2354l1.3313 1.4751c1.5505-1.399 2.5577-3.3966 2.6367-5.6401zm-3.1896-0.11231c0.048114-1.3664-0.49316-2.6214-1.3898-3.5284l-1.4372 1.3709c0.53587 0.52724 0.85713 1.2684 0.8283 2.0872-0.027911 0.79266-0.3773 1.4903-0.91815 1.9771l1.3302 1.4745c0.93172-0.83996 1.5392-2.0372 1.5865-3.3812zm-3.3161-0.11677a1.4718 1.4718 0 0 0 -0.46805 -1.1282l-1.0621 1.0128 1.0441 1.1573a1.4718 1.4718 0 0 0 0.48603 -1.0419z' color='%23000000' color-rendering='auto' dominant-baseline='auto' image-rendering='auto' shape-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3C/g%3E%3C/g%3E%3C/svg%3E");
}
.slidecontainer {
width : 100%;
}
.slider {
width : 400px;
height : 10px;
border-radius : 5px;
background : #d3d3d3;
outline : none;
opacity : 0.6;
transition : opacity 0.2s;
}
.slider:hover {
opacity : 1;
}
.slider::-webkit-slider-thumb {
appearance : none;
width : 50px;
height : 50px;
border : 0;
background-color : #4c86af;
background-image : url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='50' height='50' version='1.1' viewBox='0 0 7.9374997 7.9374997' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath d='m1.1251 0.16297h5.6586c0.54893 0 0.99084 0.44192 0.99084 0.99085v5.6586c0 0.54893-0.44192 0.99084-0.99084 0.99084h-5.6586c-0.54893 0-0.99084-0.44192-0.99084-0.99084v-5.6586c0-0.54893 0.44192-0.99085 0.99084-0.99085z' color='%23000000' fill='none' stroke='%23000' stroke-linecap='round' stroke-linejoin='round' stroke-width='.29725'/%3E%3Cpath d='m2.2644 1.612c-0.21897 0.003176-0.39387 0.18332-0.39058 0.40229v3.938c0 0.52858 0.79287 0.52858 0.79287 0v-3.938c0.0033584-0.22355-0.17873-0.40564-0.40229-0.40229zm3.3689 0c-0.21897 0.003176-0.39387 0.18332-0.39058 0.40229v3.938c0 0.52858 0.79287 0.52858 0.79287 0v-3.938c0.0033584-0.22355-0.17873-0.40564-0.40229-0.40229zm-1.6844 0c-0.21897 0.003176-0.39387 0.18332-0.39058 0.40229v3.938c0 0.52858 0.79287 0.52858 0.79287 0v-3.938c0.0033585-0.22355-0.17873-0.40564-0.40229-0.40229z' color='%23000000' color-rendering='auto' dominant-baseline='auto' fill-rule='evenodd' image-rendering='auto' shape-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3C/svg%3E");
cursor : pointer;
}
.slider::-moz-range-thumb {
width : 50px;
height : 50px;
border : 0;
background-color : #4c86af;
background-image : url("data:image/svg+xml,%3C%3Fxml version='1.0' encoding='UTF-8'%3F%3E%3Csvg width='50' height='50' version='1.1' viewBox='0 0 7.9374997 7.9374997' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath d='m1.1251 0.16297h5.6586c0.54893 0 0.99084 0.44192 0.99084 0.99085v5.6586c0 0.54893-0.44192 0.99084-0.99084 0.99084h-5.6586c-0.54893 0-0.99084-0.44192-0.99084-0.99084v-5.6586c0-0.54893 0.44192-0.99085 0.99084-0.99085z' color='%23000000' fill='none' stroke='%23000' stroke-linecap='round' stroke-linejoin='round' stroke-width='.29725'/%3E%3Cpath d='m2.2644 1.612c-0.21897 0.003176-0.39387 0.18332-0.39058 0.40229v3.938c0 0.52858 0.79287 0.52858 0.79287 0v-3.938c0.0033584-0.22355-0.17873-0.40564-0.40229-0.40229zm3.3689 0c-0.21897 0.003176-0.39387 0.18332-0.39058 0.40229v3.938c0 0.52858 0.79287 0.52858 0.79287 0v-3.938c0.0033584-0.22355-0.17873-0.40564-0.40229-0.40229zm-1.6844 0c-0.21897 0.003176-0.39387 0.18332-0.39058 0.40229v3.938c0 0.52858 0.79287 0.52858 0.79287 0v-3.938c0.0033585-0.22355-0.17873-0.40564-0.40229-0.40229z' color='%23000000' color-rendering='auto' dominant-baseline='auto' fill-rule='evenodd' image-rendering='auto' shape-rendering='auto' solid-color='%23000000' style='font-feature-settings:normal;font-variant-alternates:normal;font-variant-caps:normal;font-variant-ligatures:normal;font-variant-numeric:normal;font-variant-position:normal;isolation:auto;mix-blend-mode:normal;shape-padding:0;text-decoration-color:%23000000;text-decoration-line:none;text-decoration-style:solid;text-indent:0;text-orientation:mixed;text-transform:none;white-space:normal'/%3E%3C/svg%3E");
cursor : pointer;
}
.switch {
position : relative;
display : inline-block;
width : 70px;
height : 34px;
}
.switch input {
opacity : 0;
width : 0;
height : 0;
}
.slidersw {
position : absolute;
cursor : pointer;
top : 0;
left : 0;
right : 0;
bottom : 0;
background-color : #ccc;
transition : 0.4s;
}
.slidersw:before {
position : absolute;
content : "";
height : 26px;
width : 26px;
left : 4px;
bottom : 4px;
background-color : #4c86af;
transition : 0.4s;
}
input:checked + .slidersw {
background-color : #ddd;
}
input:focus + .slidersw {
box-shadow : 0 0 1px #ddd;
}
input:checked + .slidersw:before {
transform : translateX(34px);
}
.slidersw.round {
border-radius : 34px;
}
.slidersw.round:before {
border-radius : 50%;
}

</style>
<title>ESP Angle meter</title>
</head><body  onload="getSettings()">
<div id="header">
<div>
<button class="tabbutton tabmeasurements" type="button" onclick="toggleMeasurements()"><i class="icon-measurements"></i> Data</button>
<button class="tabbutton tabsettings" type="button" onclick="toggleSettings()"><i class="icon-settings"></i> Settings</button>
</div>
</div>
<div id="settings">
<div id="chord">
<div class="slidecontainer">
  <span class="label">Chord:</span><span id="ChordValue">50</span><span class="unit">mm</span>
  <input type="range" min="1" max="200" value="50" class="slider" id="Chord">
</div>
</div>
<div id="minmax">
<div class="slidecontainer">
  <span class="label">Min:</span><span id="MinLimitValue">50</span><span class="unit">mm</span>
  <input type="range" min="0" max="200" value="25" class="slider" id="MinLimit">
</div>
<div class="slidecontainer">
  <span class="label">Max:</span><span id="MaxLimitValue">50</span><span class="unit">mm</span>
  <input type="range" min="0" max="200" value="25" class="slider" id="MaxLimit">
</div>
</div>
<div class="buttons">
<button class="button button2" type="button" onclick="getSettings()">Load</button>
<button class="button button2" type="button" onclick="sendData(301)">Save</button>
</div>
</div>

<div id="measurements">
<div id="master">
<div class="values">
<span class="label">Angle:</span><span id="AngleValue">-180.00</span><span class="unit">deg</span><br>
<span class="label">Throw:</span><span id="ThrowValue">100</span><span class="unit">mm</span>
<label class="switch"><input type="checkbox" id="sensor1" onclick="invertAngle(1)"><span class="slidersw round"></span></label>
</div>
<div class="values">
<span class="label2">Max:</span><span id="MaxThrowValue">100</span><span class="unit">mm</span><br> 
<span class="label2">Min:</span><span id="MinThrowValue">-100</span><span class="unit">mm</span> 
</div>
<div class="buttons">
<button class="button" type="button" onclick="sendData(304)"><i class="icon-init_angle"></i> Angle</button><br>
<button class="button" type="button" onclick="sendData(303)"><i class="icon-minmax_reset"></i> Min/Max</button>
</div>
</div>
<div id="slave">
<div class="values">
<span class="label">Angle2:</span><span id="AngleValue2">-180.00</span><span class="unit">deg</span><br>
<span class="label">Throw2:</span><span id="ThrowValue2">100</span><span class="unit">mm</span>
<label class="switch"><input type="checkbox" id="sensor2" onclick="invertAngle(2)"><span class="slidersw round"></span></label>
</div>
<div class="values">
<span class="label2">Max2:</span><span id="MaxThrowValue2">100</span><span class="unit">mm</span><br>
<span class="label2">Min2:</span><span id="MinThrowValue2">-100</span><span class="unit">mm</span>
</div>
<div class="buttons">
<span class="label3">Differential</span><br><span id="DiffValue">0</span><span class="unit">%</span>
</div>
</div>
</div>
<div id="bottom"><a href="http://github.com/f5soh/aeromodeling-throw-meter"><i class="img-esplogo"></i></a></div>
<script>
document.getElementById("settings").style.display = "none";
document.getElementById("measurements").style.display = "block";
var chord_slider = document.getElementById("Chord");
var chord_display = document.getElementById("ChordValue");
var min_slider = document.getElementById("MinLimit");
var min_display = document.getElementById("MinLimitValue");
var max_slider = document.getElementById("MaxLimit");
var max_display = document.getElementById("MaxLimitValue");
//chord_display.innerHTML = chord_slider.value;
//min_display.innerHTML = min_slider.value;
//max_display.innerHTML = max_slider.value;

chord_slider.oninput = function() {
  chord_display.innerHTML = this.value;
}

min_slider.oninput = function() {
  min_display.innerHTML = this.value;
}

max_slider.oninput = function() {
  max_display.innerHTML = this.value;
}


function toggleSettings() {
if (document.getElementById("settings").style.display == "none") {
  document.getElementById("settings").style.display = "block";
  document.getElementById("measurements").style.display = "none";
}
}

function toggleMeasurements() {
if (document.getElementById("measurements").style.display == "none") {
  document.getElementById("measurements").style.display = "block";
  document.getElementById("settings").style.display = "none";
} 
  sendData(0);
}

function invertAngle(sensor){
var checkBox1 = document.getElementById("sensor1");
var checkBox2 = document.getElementById("sensor2");
if (sensor == 1) {
 if (checkBox1.checked == true){
     sendData(201);
 } else {
     sendData(200);
 }
} else if (sensor == 2) {
 if (checkBox2.checked == true){
     sendData(203);
 } else {
     sendData(202);
 }
}
};

function sendData(value) {
const xhttpcmd = new XMLHttpRequest();
xhttpcmd.open("GET", "setData?cmd=" + value + "&chord="+ chord_slider.value + "&min=" + min_slider.value + "&max=" + max_slider.value, true);
xhttpcmd.send(null);
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
 } else if (throw_value < -min_limit) {
  document.getElementById("ThrowValue").style.color = 'red';
  document.getElementById("MinThrowValue").style.color = 'red';
  document.getElementById("MaxThrowValue").style.color = 'black';
 } else {
  document.getElementById("ThrowValue").style.color = 'black';
  document.getElementById("MinThrowValue").style.color = 'black';
  document.getElementById("MaxThrowValue").style.color = 'black';
 }
 if (throw_value2 > max_limit) {
  document.getElementById("ThrowValue2").style.color = 'red';
  document.getElementById("MinThrowValue2").style.color = 'black';
  document.getElementById("MaxThrowValue2").style.color = 'red';
 } else if (throw_value2 < -min_limit) {
  document.getElementById("ThrowValue2").style.color = 'red';
  document.getElementById("MinThrowValue2").style.color = 'red';
  document.getElementById("MaxThrowValue2").style.color = 'black';
 } else {
  document.getElementById("ThrowValue2").style.color = 'black';
  document.getElementById("MinThrowValue2").style.color = 'black';
  document.getElementById("MaxThrowValue2").style.color = 'black';
 }

 if (slave_found != "false") {
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
this.slave_found = "undefined";
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

function getSettings() {
const xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function(event) {
 if (this.readyState === XMLHttpRequest.DONE && this.status === 200) {
  var str_in = this.responseText;
  var words = str_in.split(':');
  document.getElementById("ChordValue").innerHTML = words[0];
  chord_slider.value = words[0];
  document.getElementById("MinLimitValue").innerHTML = words[1];
  min_slider.value = words[1];
  document.getElementById("MaxLimitValue").innerHTML = words[2];
  max_slider.value = words[2];
 }
};
xhttp.open("GET", "readSettings", true);
xhttp.send(null);
}
</script>
</body></html>
)=====";
