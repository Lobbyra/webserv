<!DOCTYPE HTML>
<html>
<head>
<title>Drunkserv: Year countdown</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
p {
  text-align: center;
  font-size: 60px;
  margin-top: 0px;
}
</style>
</head>
<body>
<center>
    <h1>Time remaining before the end of the yeah(r) !</h1>
</center>

<p id="demo"></p>

<script>
var countDownDate = new Date("Dec 31, 2021 23:59:59").getTime();

var x = setInterval(function() {

  var now = new Date().getTime();
    
  var distance = countDownDate - now;
    
  var days = Math.floor(distance / (1000 * 60 * 60 * 24));
  var hours = Math.floor((distance % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));
  var minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));
  var seconds = Math.floor((distance % (1000 * 60)) / 1000);
    
  document.getElementById("demo").innerHTML = days + "d " + hours + "h "
  + minutes + "m " + seconds + "s ";
    
  if (distance < 0) {
    clearInterval(x);
    document.getElementById("demo").innerHTML = "EXPIRED";
  }
}, 1000);
</script>

<center>
<iframe src="https://giphy.com/embed/dljfxXgllDJviK6W3c" width="480" height="480" frameBorder="0" class="giphy-embed" allowFullScreen></iframe><p><a href="https://giphy.com/gifs/HostGator-new-year-2021-years-eve-dljfxXgllDJviK6W3c"></p>
</center>

</body>
</html>
