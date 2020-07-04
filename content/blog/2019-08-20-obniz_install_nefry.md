+++
title = "obniz OSをESP32(NefryBT)に入れて動かそう！"
date = 2019-08-20
draft = false
author = "wami"
categories = ["obniz","nefry"]
tags = ["obniz","nefry"]
description = "obniz OSをESP32(NefryBT)に入れて動かそう！"
featured = ""
featuredalt = ""
featuredpath = ""
linktitle = "obniz OSをESP32(NefryBT)に入れて動かそう！"
type = "post"

+++

こんにちは！わみです！
今日は先日リリースされたobnizOSを使い始めてみたので、どんな感じなのかも合わせて書いていこうと思います。

そもそも「obniz」ってなに？って方は「[arduinoとは全く違う、IoTツールobnizのしくみ](https://qiita.com/wicket/items/546c2900bda7c8c85a60)」をご覧ください。

# なにができるのか

<blockquote class="twitter-tweet"><p lang="ja" dir="ltr">NefryでobnizOS動いた！！ <a href="https://t.co/YAbw8ggR5B">pic.twitter.com/YAbw8ggR5B</a></p>&mdash; わみ@NefryとかFlutter本とか (@wamisnet) <a href="https://twitter.com/wamisnet/status/1162662514829565953?ref_src=twsrc%5Etfw">August 17, 2019</a></blockquote> <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>

HTML+JSでハードウエア(ESP32(NefryBT))を動かしてみた動画です！

JavaScriptやpythonでハードウエアを動かすことができる「obniz」ただ、6000円近くするので少々お値段がします…

![](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/5d7decc2-74b6-0f2b-55c5-a019b84833a0.jpeg)

その技術をお店で1500円ぐらいで売っているESP32のボードにインストールができるのが先日発表された「obnizOS」なのです！

![](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/9543988c-f5b3-188f-8062-721bae769a7b.png)

私が作っている「Nefry BT」というデバイスにインストールしてみたのでその方法とどんな感じなのかをまとめてみようと思います。
ESP32を搭載したボードであれば、同じような手順で行うことができるのでぜひお試しください。

（ESP32-picoについては未サポート（具体例：M5stickC））

# インストール

## ライセンスを購入する

https://obniz.io/ja/console
上記ページから「デバイス」を選択し、「obniz OSのライセンスを新規購入」をクリックします。

![](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/2d1e5fc8-e161-2d70-a31f-a38b3909231c.png)


ライセンスの選択画面で「Hobby」ライセンス、「新規にobnizIDを発行」、個数を選び、「金額を確認」をクリックします。
カードの情報がない場合、このタイミングで入力します。

![](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/f1c39a86-4f57-3020-bbba-04b84fc32d91.png)


確認画面が表示されて、問題なければ「ライセンスを購入」を押します。

![](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/b25db3e9-40fd-83ef-484f-529a6df57479.png)


購入が完了すると、「DeviceKey」をダウンロードできます。
これはインストール時に使用するので必ずダウンロードしておいてください。
（画像取り忘れたので公式ドキュメントの画像…）

![](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/d2ff5985-e1b3-98b9-1df0-9a23882d96f3.png)


## 前提条件

obniz cliを使用しますのでpython3.4以上のものをインストールしておいてください。

```py -3 -V```でバージョン情報を確認することができます。
インストールされていれば、上記のコマンドをターミナルで実行すると次のようにバージョンが表示されます。

![](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/8fa7428c-ac2c-7e35-85a1-0543e5904219.png)


表示されない場合は、インストールされているか確認したり、pathが通っているか確認してください。

## obniz_cliをインストール

obniz_cliとは、簡単にobnizOSをインストールするために作られたアプリになります。それを使って、セットアップを行っていきたいと思います。

ターミナルで```pip3 install obniz_cli```と入力します。

インストールが開始されるはずです！「Successfully installed obniz_cli」とでれば大丈夫です。

![](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/6321e9b7-24e4-0433-030d-3590fb2ff816.png)


## Nefry BTにobnizOSをインストール

Nefry BTをPCと接続し、obnizOSをインストールしていこうと思います。

ターミナルで```obniz_cli flashos```と入力します。

ESP32を接続しているポートを選択画面がでるので、ポートの横に書かれている数字（今回なら0）を入力します。ここで選んだポート名（今回ならCOM5）を覚えておいてください。

入力するとインストールが開始されます。

![](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/4ca4afb0-04a9-3f85-d3de-aa023d6fa9d2.png)

しばらくするとインストールが完了します。

次に無線LANの設定とライセンスの適用を行っていきます。

ターミナルで```python -m serial.tools.miniterm ポート名 115200```と入力します。

ポート名は先ほど選んだものに変更しておいてください。

指示に従って、次の項目を入力します。

- DeviceKey:購入時に取得したファイルに書かれた文字列
- SSID:接続したい無線LANのもの
- PASS:接続したい無線LANのもの
- 固定IP or DHCP:基本的にはDHCPの「0」を選択する
    - 固定IPの場合 下記の項目を設定する
        - IP Address
        - Subnetmask
        - Default gateway

![](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/a15e03f1-0c68-2b41-5998-d833870ca9c3.png)

設定された項目が正しければ、最後に「Online」と表示されます。

正しくない場合、再度正しいデータを入力されるように求められるので再度行ってください。

# JavaScriptでコードを書いてみる

JavaScriptでハードウエアが動かせるので少しコードを書いてみました。

なにがよいか私なりのメリットを挙げてみます。

- HTMLと合わせて簡単に操作画面をつくれるところ
- 開発環境を作成しなくてよいところ（公式サイトにエディタがある）
- いくつかの部品のライブラリがあるのも始めやすいところ
https://obniz.io/ja/sdk/parts/LED/README.md
![](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/6d20e84e-4e37-ef18-84a6-a3cacd11587b.png)

みたいなところですかね！ここもメリットだよってのがあれば教えてもらえると！

## 動かしてみる

「Nefry BT」で動かせるようにボタンとフルカラーLEDをコントロールするプログラムをJavaScriptで書いてみたので試してみましょう！

http://obniz.io/ja/console/program

上記のURLをクリックすると、購入したobniz idが選択できるはずです。

![](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/ba566780-550d-e53a-930c-079e7dc5d9cd.png)

選択して、「開く」を押してみましょう！

NefryBTではない別のESP32ボードの場合はそのままサンプルプログラムを動かしてみましょう！

サンプルプログラムがあるので一旦削除して、次のコードを貼りましょう！
コード内にある「your obniz id」と書かれたところを先ほど選んだobniz idに置き換えることを忘れないでください！

```html
<html>
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css">
    <script src="https://obniz.io/js/jquery-3.2.1.min.js"></script>
    <script src="https://unpkg.com/obniz@2.2.0/obniz.js" crossorigin="anonymous"></script>
  </head>
  <body>

    <div id="obniz-debug"></div>
    <h3>obnizOS on Nefry</h3>
    <button class="btn btn-primary m5" id="on">ON</button>
    <button class="btn btn-primary m5" id="off">OFF</button>

    <script>
      var obniz = new Obniz("your obniz id");

      obniz.onconnect = async function () {
        var color = obniz.wired("WS2812", {din: 16});
        color.rgb(0xFF, 255, 0);
        var led = obniz.wired("LED", {anode:26}); // io0 is anode. cathode is connected obniz GND other way.

        obniz.getIO(4).pull("3v");
        obniz.getIO(4).input(function(value){
          console.log("changed to " + value);
          color.rgb(Math.floor( Math.random() * (256) ), Math.floor( Math.random() * (256) ), Math.floor( Math.random() * (256) ));
        });
        $("#on").click(function(){
          led.on();
        })

        $("#off").click(function(){
          led.off();
        })
      }

    </script>
  </body>
</html>
```

![](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/95b1b8e2-d2b5-8cb9-5f37-c1bc25bfff80.png)

貼り付けたら、右上の「実行」ボタンを押してください。

Nefry BTのSWを押すと、フルカラーLEDがランダムに光ります。
HTMLのボタンを押すと、26ピンに接続されたLEDが点灯したり、消灯したりします。

### ピンの指定

ESP32のピン番号を直接指定します。

Nefryの場合、直接基板上に書かれていないので、次の画像を参考にしてください。

- Nefry BT(無印)

![nefrybt_pinmap.png](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/84c35176-f56e-2813-568f-44ef80122c4e.png)

- Nefry BT R2/R3

![NefryBTr2_r3_pinmap.png](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/29718b0d-2560-747b-97d6-04f0803938dc.png)

# まとめ

obniz OSでこれからもっと便利にIoTを始められるようになるのではないでしょうか？

コードの使い勝手としては、obnizボードと大差ない気がします。ただ、ReadOnlyのIOやアナログ入力など制約があるところやモータドライバーがついていないのでモータを直接動かせないところもあるのでそのあたりはobnizボードのところが優れてるかなと思います。

Nefry BTではArduinoでコードを書くのが普通ですが、JavaScriptであったとしても私としてはハードウエアが好きになって、いろんなものが生まれてくるとすごくいいなと思っています。

# ここまで読んでくれた方へ

ここまで読んでくださりありがとうございます。

いいねやコメント、SNSでの共有等をしてくださると、今後の励みになります。よろしくお願いします。

良かったら[Twitter](https://twitter.com/wamisnet)もフォローしてね
