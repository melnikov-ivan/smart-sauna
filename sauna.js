document.body.innerHTML = '\
<div>\
<h1>Баня</h1>\
<table>\
<tr><td>\
  <h2>Бак 1</h2>\
  <div id="sensor-bak_1_temp"></div>\
  <div id="sensor-bak_1_level"></div>\
  </td><td>\
  <h2>Бак 2</h2>\
  <div id="sensor-bak_2_temp"></div>\
  <div id="sensor-bak_2_level"></div>\
</td></tr>\
<tr><td>\
  <h2>Комната 1</h2>\
  <div id="sensor-room_1_temperature"></div>\
  <div id="sensor-room_1_humidity"></div>\
  <div id="sensor-room_1_battery"></div>\
  </td><td>\
  <h2>Комната 2</h2>\
  <div id="sensor-room_2_temperature"></div>\
  <div id="sensor-room_2_humidity"></div>\
  <div id="sensor-room_2_battery"></div>\
</td></tr>\
<tr><td>\
  <h2>Комната 3</h2>\
  <div id="sensor-room_3_temperature"></div>\
  <div id="sensor-room_3_humidity"></div>\
  <div id="sensor-room_3_battery"></div>\
  </td><td>\
  <h2>Комната 4</h2>\
  <div id="sensor-room_4_temperature"></div>\
  <div id="sensor-room_4_humidity"></div>\
  <div id="sensor-room_4_battery"></div>\
</td></tr>\
</div>\
';
const source=new EventSource("/events");
source.addEventListener("state",function(a){const b=JSON.parse(a.data);document.getElementById(b.id).innerText=b.state});