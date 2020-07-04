+++
title = "UniboでAzure IoTHubと連携させてみる"
date = 2017-05-10
draft = false
author = "wami"
categories = ["AzureIoTHub","Unibo"]
tags = ["AzureIoTHub","Unibo"]
description = "UniboでAzure IoTHubと連携させてみる"
featured = ""
featuredalt = ""
featuredpath = ""
linktitle = "UniboでAzure IoTHubと連携させてみる"
type = "post"

+++

# AzureIoTHubでメッセージを送受信してみる。
Azure IoTHubとUniboのメッセージをやりとりしてみましょう。

##全体図

```
[{"id":"1a885986dc.5c17f8","type":"tab","label":"iothub"},{"id":"1adc54aae1.2cb078","type":"inject","z":"1a885986dc.5c17f8","name":"開始","topic":"","payload":"","payloadType":"date","repeat":"","crontab":"","once":false,"x":320,"y":324.888916015625,"wires":[["1a50458b29.daf934"]]},{"id":"1a5b568748.b15d28","type":"azureiothub","z":"1a885986dc.5c17f8","name":"Azure IoT Hub","protocol":"mqtt","x":958.1041870117188,"y":325,"wires":[["1a452ce6f4.4d1838"]]},{"id":"1a6872e007.3f029","type":"template","z":"1a885986dc.5c17f8","name":"Azure IoTHubに接続情報","field":"payload","fieldType":"msg","format":"json","syntax":"mustache","template":"{\n  \"deviceId\": \"unibo\",\n  \"key\": \"SharedAccessKey=以下のものを貼る\",\n  \"protocol\": \"mqtt\",\n  \"data\": \"{value1: 0, value2: \\\"test\\\"}\"\n}","x":718.1041870117188,"y":325,"wires":[["1a5b568748.b15d28"]]},{"id":"1ad307ac75.70343","type":"motion","z":"1a885986dc.5c17f8","name":"","target":"other","motion":"happy","x":1042.1041870117188,"y":561,"wires":[[]]},{"id":"1a9501606e.fe849","type":"debug","z":"1a885986dc.5c17f8","name":"","active":true,"console":"false","complete":"payload","x":747.1041870117188,"y":432,"wires":[]},{"id":"1a50458b29.daf934","type":"led","z":"1a885986dc.5c17f8","name":"","color":"black","version":1,"x":499.10418701171875,"y":325,"wires":[["1a6872e007.3f029"]]},{"id":"1a452ce6f4.4d1838","type":"function","z":"1a885986dc.5c17f8","name":"データ整形","edit":"","func":"msg.payload = msg.payload.toString();\nreturn msg;","outputs":1,"dummy":"1","noerr":0,"x":336.10418701171875,"y":485,"wires":[["1a513c662f.d3f0a8"]]},{"id":"1a513c662f.d3f0a8","type":"switch","z":"1a885986dc.5c17f8","name":"送受信分岐","property":"payload","propertyType":"msg","rules":[{"t":"eq","v":"Message sent.","vt":"str"},{"t":"neq","v":"Message sent.","vt":"str"}],"checkall":"true","outputs":2,"x":521.1041870117188,"y":485,"wires":[["1a9501606e.fe849"],["1a14de07ea.ded998"]]},{"id":"1a14de07ea.ded998","type":"delay","z":"1a885986dc.5c17f8","name":"","pauseType":"rate","timeout":"5","timeoutUnits":"seconds","rate":"1","nbRateUnits":"30","rateUnits":"second","randomFirst":"1","randomLast":"5","randomUnits":"seconds","drop":false,"x":764.1041870117188,"y":526,"wires":[["1ad307ac75.70343"]]},{"id":"1a7c821ed2.91754","type":"delay","z":"1a885986dc.5c17f8","name":"","pauseType":"timed","timeout":"5","timeoutUnits":"seconds","rate":"1","nbRateUnits":"30","rateUnits":"second","randomFirst":"1","randomLast":"5","randomUnits":"seconds","drop":false,"x":771.1041870117188,"y":621,"wires":[["1ad307ac75.70343"]]},{"id":"1a289d2a8d.919826","type":"comment","z":"1a885986dc.5c17f8","name":"AzureIoTHubで必要となる情報を入力します。","info":"","x":736.1041870117188,"y":275,"wires":[]},{"id":"1af14fac81.3eab5","type":"comment","z":"1a885986dc.5c17f8","name":"３０秒毎に順番に処理をします","info":"","x":774.1041870117188,"y":485,"wires":[]},{"id":"1a63ab930e.7d0b8c","type":"comment","z":"1a885986dc.5c17f8","name":"３０秒の間に届いた最新のメッセージの処理をします","info":"","x":767.1041870117188,"y":672,"wires":[]}]
```

![2017-05-10_16h22_40.png](https://qiita-image-store.s3.amazonaws.com/0/97208/30c4a9c2-fb76-5d1f-acc1-f07e0c0ea457.png)

## 前提条件

- Azureに登録できていること

## 手順

AzureのIoTHubに登録するところから説明していきます。

##Azure IoTHubの設定
それでは、AzureにログインしてIoTHubを実際に作っていきましょう！

[Azure ポータル](https://portal.azure.com/)を開いていきます。

新規からモノのインターネット(IoT)をクリックして、IoTHubをクリックします。これから必要な設定を行っていきます。
![qiita (1).png](https://qiita-image-store.s3.amazonaws.com/0/97208/ce4352be-1343-811e-9aff-3c9564616c34.png)

無事にIoTHubが開かれると複数の入力欄が出るので写真を参考に入力欄を埋めていきましょう。
それでは、必須項目であるIoTHubの名前を入力してください。この名前はドメインでも使われますので他の方と重複するとエラーが出ます。入力欄の右端が緑のチェックが入れば大丈夫です。
次に、価格とスケールティアを変更していきます。この際に**Free**を必ず選んでください。Standardを選んだまま作成してしまうと、後からFreeに変更することができず、再度作り直すことになります。

Freeを選択したらクリックして反映させてください。

![qiita (2).png](https://qiita-image-store.s3.amazonaws.com/0/97208/b6ba0433-2f3b-5880-a64a-984963454857.png)

リソースグループは既存ものがあれば、それを使って頂いてもかまいませんが、今回は初めてだという前提で、新規作成で好きなグループ名を入力してください。

Azureサーバーがある場所を指定することができます。東日本、西日本と選べますのでお好みでどうぞ。

ここまで問題なくできていれば、作成ボタンをクリックしてIoTHubをデプロイしていきます。
![qiita (3).png](https://qiita-image-store.s3.amazonaws.com/0/97208/a90ad588-662f-cef3-9a93-0a88d64a35dc.png)

数分かかりますのでしばしお待ちを…
![qiita (4).png](https://qiita-image-store.s3.amazonaws.com/0/97208/b1f92c09-8b7c-051b-a98c-4ec83906cf78.png)

無事にIoTHubのデプロイが終わるとこのような画面が表示されます。
この画面では先ほど設定した内容が見れるほか、IoTHubの使用状態を確認することができます。

![qiita (5).png](https://qiita-image-store.s3.amazonaws.com/0/97208/bdb67499-38b0-1423-a67f-0b3b97ded178.png)


デバイスを繋げるために必要な設定を行っていきます。
共有アクセスポリシーから**iothubowner**をクリックし、プライマリキーをコピーします。
このとき写真で示してある部分をクリックすると簡単にキーをコピーすることができます。

このプライマリキーは次の作業で使用します。
![qiita (6).png](https://qiita-image-store.s3.amazonaws.com/0/97208/0c2bfdd1-e227-a1f5-6cce-ca7b3c4a2293.png)

この作業から**Device Explorer**というツールを使っていきます。
このツールはWindows専用になります。MacやLinuxの場合**iothub-explorer**を使うようですが、今回は取り扱いません。

###Device Explorerのダウンロード
こちらの**[リンク](https://github.com/Azure/azure-iot-sdk-csharp/releases/download/2017-5-5/SetupDeviceExplorer.msi)**からダウンロードしてインストールをよろしくお願いします。

インストールが終わったところで**Device Explorer**を使っていこうと思います。

このツールでIoTHubに接続できる端末の登録、削除、ほかにはデバイスからIoTHubへの通信モニターになったり、IoTHubからデバイスにデータを送ることができるなどIoTHubに必須のものとなっております。

説明が長くなりましたが、それではこのDevice Explorerに先ほどのプライマリキーを入力して**Update**をクリックしてください。
![qiita (7).png](https://qiita-image-store.s3.amazonaws.com/0/97208/807dd4d5-c20e-efe9-7762-7a25b14ddb93.png)

プライマリキーが合っていれば、このような表示がされます。この表示がでれば先ほど作ったIoTHubと連携ができるようになります。
![qiita (8).png](https://qiita-image-store.s3.amazonaws.com/0/97208/f292ae2d-df6a-fb4d-d840-387815e711b2.png)
これからIoTHubに接続できるデバイスの設定をしていこうと思います。

この作業はデバイスごとにIDを割り振る作業になります。
ManagementからCreateをクリックします。
![qiita (9).png](https://qiita-image-store.s3.amazonaws.com/0/97208/f4126134-e9d6-aff1-357c-87f5b8ea69ba.png)
Createをクリックするとこのような画面が出ますので、Device IDに接続するデバイス名を入力してください。

入力が終わったらCreateをクリックしてください。
![qiita (10).png](https://qiita-image-store.s3.amazonaws.com/0/97208/38317460-b23e-cae6-ee33-36a893d7b596.png)


無事にデバイスが作れると先ほどのDevice IDを持ったものが増えているはずです。
![qiita (11).png](https://qiita-image-store.s3.amazonaws.com/0/97208/552087c4-b0e7-fe1c-a726-591d6e9a6ca2.png)

無事に作成できていれば、次はデバイスに必要な情報をコピーしておきましょう。
今回作成したDevice IDをクリックすると青色の欄が移動しますので、選択された状態で右クリックすると**Copy connection string for selected device**を選んでクリックしてください。

そうすると必要な情報がコピーされますので、その情報をUniboに登録していきます。
![qiita (12).png](https://qiita-image-store.s3.amazonaws.com/0/97208/278d5b44-99f2-afff-c4da-38a86df31fa9.png)

## スキルクリエイターの設定をしよう

前もって、スキルクリエイターにログインし、全体図の章に書いてあるjsonファイルをスキルクリエイターにインポートします。

インポートができたらAzure IoTHubに接続するために必要な情報を入力していきます。

今回はテンプレートNodeに必要な情報を入力します。動的に切り替えて接続先を変更することなども可能ですが今回はシンプルに作成します。

| タイトル  | 入力内容 |
|:--------:|:-----------------------:|
| deviceId | Device Explorerでデバイス登録時に入力したDeviceID |
| key      | Device Explorerで取得した**Copy connection string for selected device**をkeyと書かれた欄に貼り付けします。一例ですが```HostName=unibo.azure-devices.net;DeviceId=unibo;SharedAccessKey=tIrfnS6csQ=```このように貼り付けされます。今回必要となるのは**SharedAccessKey**の部分となります。上の例であれば```tIrfnS6csQ=```となります。**それ以外は削除してください。** |
| protocol | http,mqtt,AMQPから選択 |
| data     | Azure IoTHubに送信したいデータ |


![2017-05-10_17h01_08.png](https://qiita-image-store.s3.amazonaws.com/0/97208/5aaa13e3-a8c7-c613-3da6-aa0039899788.png)

次にAzure IoTHub Nodeを設定していきます。
設定項目としては、Hostnameに必要な情報を入力します。
先ほども使ったDevice Explorerで取得した**Copy connection string for selected device**をHostnameに貼り付けします。
一例ですが```HostName=unibo.azure-devices.net;DeviceId=unibo;SharedAccessKey=tIrfnS6csQ=```このように貼り付けされます。
今回必要となるのは**HostName**の部分となります。上の例であれば```unibo.azure-devices.net```となります。
**それ以外は削除してください。**

![2017-05-10_17h26_20.png](https://qiita-image-store.s3.amazonaws.com/0/97208/44f3b8e3-dd51-8cea-3233-eccff7559bde.png)

Azure IoTHubとしての設定はこれまでのもので完了です。
あとはAzure IoTHubからのデータを受信したときにどのような動作をするのかこれから順に説明していきます。

![2017-05-10_17h47_03.png](https://qiita-image-store.s3.amazonaws.com/0/97208/3acbf960-397d-bac7-2207-c5ffff7c84d6.png)

###データ整形

Azure IoTHub Nodeでは送信時と受信時にNodeを通ります。**送信時にも下のNodeにイベントが行くので注意が必要となります。**

受信時にイベントが発火する場合、データがHEXデータでくるので文字列として活用したい場合は関数Nodeで変換してください。

```javascript
msg.payload = msg.payload.toString();
return msg;
```

このように変換することで文字列として扱えるようになりました。

その後、送信なのか受信なのかを判定しています。その際の判定は```Message sent.```という言葉がメッセージに含まれているかで判定することができます。
これにより、受信時のみUniboを動かすことができるようになりました。

### 受信時の処理

受信時にも注意が必要となります。
Azure IoTHubから別々のデータがネットワークなどの影響でまとめて届く場合があります。

この時に対策を取っていないと、Nodeが続々と発火する可能性があります。例としては、Uniboの動作が完了せずに終了することやUniboの発話が完了せずに終了するなど予期しない動作をする可能性があります。

対策としては、delay Nodeにて「レートの制限」や「時限リリースキュー」などがあります。もしくはグローバル変数などを用いフラグ管理するなどで対応することが可能です。

#まとめ

UniboとAzure IoTHubを使うことで外部との連携が簡単にできるようになります。
Azure IoTHubを使うことでハードウエアはもちろん、Webとの連携もできるのでぜひ試してみてください。
