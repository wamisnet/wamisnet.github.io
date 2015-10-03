
/////////////////////////////////////
// view functions
/////////////////////////////////////
var CV = document.getElementById('canvas'), CX = CV.getContext('2d');

var ACCEL = [0, 0, 0], ACCEL_X = [], ACCEL_Y = [], ACCEL_Z = [];
(function() {
  for (var i = 0; i < 256; ++i)
    ACCEL_X[i] = ACCEL_Y[i] = ACCEL_Z[i] = 0;
})();

var angle={};
angle.x = 0;
angle.y = 0;
angle.z = 0;
window.addEventListener('devicemotion', function(evt) {
/*  var xg = evt.acceleration.x; // 加速度X
  var yg = evt.acceleration.y; // 加速度Y
  var zg = evt.acceleration.z; // 加速度Z    
  ACCEL = [xg, yg, zg];*/
  var xg = evt.accelerationIncludingGravity.x; // 横方向の傾斜
  var yg = evt.accelerationIncludingGravity.y; // 縦方向の傾斜
  var zg = evt.accelerationIncludingGravity.z; // 上下方向の傾斜    
  angle.y = Math.sin(Math.atan2(yg,zg));       // -1.0 ～　1.0　に変換
  angle.x = Math.sin(Math.atan2(xg,zg));
  angle.z = Math.sin(Math.atan2(yg,xg));
  ACCEL = [angle.x, angle.y, angle.z];
  document.getElementById("aionum").innerHTML = "傾きｘ:"+angle.x.toFixed(3)+" y:"+angle.y.toFixed(3)+" z:"+angle.z.toFixed(3);
      var txt  = "x:"+x+"<br>";
        txt += "y:"+y+"<br>";
        txt += "z:"+z+"<br>";

        txt += "傾きx:"+xg+"<br>";
        txt += "傾きy:"+yg+"<br>";
        txt += "傾きz:"+zg+"<br>";

        txt += "alpha(z):"+a+"<br>";
        txt += "beta(x):"+b+"<br>";
        txt += "gamma(y):"+g+"<br>";

    console.log(txt);

}, true);

function normal(v) {
  return v * 128 + 128;
}

function draw(data, color, next) {
  CX.strokeStyle = color;
  CX.beginPath();
  CX.moveTo(0, normal(data[0]));
  for (var i = 1; i < 256; ++i) CX.lineTo(i, normal(data[i - 1] = data[i]));
  data[255] = next;
  CX.stroke();
}

function update() {
  CX.clearRect(0, 0, 256, 256);
  CX.fillStyle = '#ccd';
  CX.fillRect(0, 0, 256, 256);
  CX.strokeStyle = 'rgba(0,0,0,0.2)';
  for (var i = 0; i <= 256; i += 32) {
    CX.beginPath();CX.moveTo(0, i);CX.lineTo(255, i);CX.stroke();
    CX.beginPath();CX.moveTo(i, 0);CX.lineTo(i, 255);CX.stroke();
  }
  draw(ACCEL_X, 'rgba(255,0,0,0.9)', ACCEL[0]);
  draw(ACCEL_Y, 'rgba(0,255,0,0.9)', ACCEL[1]);
//  draw(ACCEL_Z, 'rgba(0,0,255,0.9)', ACCEL[2]);
}
var cmdX = 0;
var cmdY = 0;
var lastCmdX = 0;
var lastCmdY = 0;
function startUpdate(){
    
    setInterval(function(){
        update();
        cmdX = Math.floor(angle.y * 100);
        cmdY = Math.floor(angle.x * 100);
        if( (angle.x >=-0.25 && angle.x <= 0.25) && (angle.y >=-0.25 && angle.y <= 0.25)) {
          //BT.WRITE "M,0,0"
            if((lastCmdX !== 0)||(lastCmdY !== 0)) {
                sendCommand("M,0,0\r");
                lastCmdX = 0;
                lastCmdY = 0;
            }
        } else if((angle.y < -0.25 || angle.y > 0.25) && (angle.x >=-0.25 && angle.x <= 0.25)){
          //BT.WRITE "M," + REPLACE$(FORMAT$("%%%", y ) ," ","") + ",0"
//            sendCommand("M," + Math.floor(angle.y * 100) + ",0\r");
            if(cmdX != lastCmdX) {
                sendCommand("M," + cmdX + ",0\r");
                lastCmdX = cmdX;
            }
        } else if ((angle.x < -0.25 || angle.x > 0.25) && (angle.y >=-0.25 && angle.y <= 0.25)) {
          //BT.WRITE "T," + REPLACE$(FORMAT$("%%%", x ) ," ","") + ",0"
//            sendCommand("T," + Math.floor(angle.x * 100) + ",0\r");
            if(cmdY != lastCmdY) {
                sendCommand("T," + cmdY + ",0\r");
                lastCmdY = cmdY;
            }
        } else {
          //BT.WRITE "M,0,0"
            if((lastCmdX !== 0)||(lastCmdY !== 0)) {
                sendCommand("M,0,0\r");
                lastCmdX = 0;
                lastCmdY = 0;
            }
        }
        
    }, 300);
}
  
$(function(){
    $("#button").tap(function(){
        k.find();
    });
});
/*
$(function(){
    $("#btnpio1").bind('touchstart',function(){
        //k.digitalWrite(k.PIO1, k.HIGH);
        board.digitalWrite(ledPin2, board.HIGH);
    });
});

$(function(){
    $("#btnpio1").bind('touchend',function(){
        //k.digitalWrite(k.PIO1, k.LOW);
        board.digitalWrite(ledPin2, board.LOW);
    });
});
*/
function showFirst(){
    $("#content").animate(
        {left: "0%"},
        {duration: 500, easing: "ease-in-out"}
    );
}

function showConnecting(){
    $("#content").animate(
        {left: "-100%"},
        {duration: 500, easing: "ease-in-out"}
    );
}

function showPio(){
    $("#content").animate(
        {left: "-200%"},
        {duration: 500, easing: "ease-in-out"}
    );
}
/*
function changePio0(value){
    if(value & 0x01){
        $("#num").html("ON");
        board.digitalWrite(ledPin3, board.HIGH);
    }else{
        $("#num").html("OFF");
        board.digitalWrite(ledPin3, board.LOW);
    }
}*/
function showMeter(){
    $("#content").animate(
        {left: "-200%"},
        {duration: 500, easing: "ease-in-out"}
    );
}

function changeMeter(value){
    $("#meter").animate(
        {height: (value/1.30)*100 + "%"},
        {duration: 500, easing: "ease-in-out"}
    );
    $("#aionum").html(value.toFixed(3));
}

function sendCommand(data) {
      for(i=0;i<data.length;i++){
        k.uartWrite(data.charCodeAt(i));
      }
}

