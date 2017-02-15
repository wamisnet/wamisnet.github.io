window.AudioContext = window.AudioContext || window.webkitAudioContext;
var context = new AudioContext();

// Audio 用の buffer を読み込む
var getAudioBuffer = function(url, fn) {  
  var req = new XMLHttpRequest();
  // array buffer を指定
  req.responseType = 'arraybuffer';

  req.onreadystatechange = function() {
    if (req.readyState === 4) {
      if (req.status === 0 || req.status === 200) {
        // array buffer を audio buffer に変換
        context.decodeAudioData(req.response, function(buffer) {
          // コールバックを実行
          fn(buffer);
        });
      }
    }
  };

  req.open('GET', url, true);
  req.send('');
};

// サウンドを再生
var playSound = function(buffer) {
  // source を作成
  var source = context.createBufferSource();
  // buffer をセット
  source.buffer = buffer;
  // context に connect
  source.connect(context.destination);
  // 再生
  source.start(0);
};

    var milkcocoa = new MilkCocoa("guitariptgbiyq.mlkcca.com");
    var ds = milkcocoa.dataStore('nefry');
    ds.on('push', function(pushed) {
        if(pushed.value.sw=='1'){        
           document.getElementById("cb").checked = true;
           getAudioBuffer('fm.mp3', function(buffer) {playSound(buffer);});
        }else if(pushed.value.sw=='0'){
            document.getElementById("cb").checked = false;
        }
    });
