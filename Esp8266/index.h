const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
  <script>
    function loadSensor(param, holder) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById(holder).innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", param, true);
  xhttp.send();
}
  </script>
</head>
<body>
  <h2>Sauna</h2>
  <table>
  <tr>
  <td>
  <p>
   Temperature <span id="temp1"/>
  </p>
  <p>
    Level <span id="level1"/>
  </p>
  </td>
  <td>
    <p>
      Temperature <span id="temp2"/>
    </p>
    <p>
      Level <span id="level2"/>
    </p>
  </td>
  </tr>
  </table>

</body>
<script>
  setInterval(loadSensor, 4900, "/t1", "temp1");
  setInterval(loadSensor, 6300, "/l1", "level1");
  setInterval(loadSensor, 4900, "/t2", "temp2");
  setInterval(loadSensor, 6300, "/l2", "level2");
</script>
</html>
)rawliteral";
