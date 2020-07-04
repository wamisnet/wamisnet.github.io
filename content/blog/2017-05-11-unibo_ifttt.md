+++
title = "UniboとIFTTTで簡単にIoTしてみる"
date = 2017-05-11
draft = false
author = "wami"
categories = ["Unibo"]
tags = ["Unibo"]
description = "UniboとIFTTTで簡単にIoTしてみる"
featured = ""
featuredalt = ""
featuredpath = ""
linktitle = "UniboとIFTTTで簡単にIoTしてみる"
type = "post"

+++

IFTTTは（イフト）TwitterやFacebook、SlackなどのWebサービス同士を組み合わせて簡単に連携できるサービスです。

今回はそのIFTTTとUniboをつなげてUniboからSlackやTwitterなどにメッセージを送信する仕組みについて説明します。

#全体図

```
[{"id":"1a22c6251f.020e3a","type":"tab","label":"IFTTT"},{"id":"1ad734c9dd.af1808","type":"http request","z":"1a22c6251f.020e3a","name":"IFTTTにアクセス","method":"GET","ret":"txt","url":"","tls":"","x":586,"y":440,"wires":[["1a70e6eb3f.c26754"]]},{"id":"1ad02e9d78.efebc","type":"speech","z":"1a22c6251f.020e3a","word":"","subtitle":"","name":"","edit":false,"language":"jp","voice":"yuuto","version":1,"x":987,"y":440,"wires":[[]]},{"id":"1a70e6eb3f.c26754","type":"function","z":"1a22c6251f.020e3a","name":"発話のためにコピー","edit":"","func":"msg.word = msg.subtitle = msg.payload;\nreturn msg;","outputs":1,"dummy":"1","noerr":0,"x":805,"y":440,"wires":[["1ad02e9d78.efebc"]]},{"id":"1a8a30f02a.12783","type":"inject","z":"1a22c6251f.020e3a","name":"","topic":"","payload":"","payloadType":"date","repeat":"","crontab":"","once":false,"x":390,"y":440,"wires":[["1ad734c9dd.af1808"]]}]
```

![](https://qiita-image-store.s3.amazonaws.com/0/97208/f41038fa-81ab-0c66-4805-9c271720cbdc.png)

#手順

IFTTTの登録についてはこちらの記事をご覧ください。
>[Webサービス同士を連携できる「IFTTT」と自作IoTデバイスを繋いで生活を便利にしてみた](https://liginc.co.jp/263899)

登録ができたところで、実際に連携させてみようと思います。
## IFTTTでシナリオを作成してみる

[IFTTT](https://ifttt.com/create)でUniboとLineをつなげるレシピと呼ばれるシナリオを作成していきます。
上のリンクをクリックして作成していきましょう。

![](https://qiita-image-store.s3.amazonaws.com/0/97208/ec9d9bc7-10fe-c0f5-0603-be8d604772b5.png)

まずはMakerWebhooksをトリガーにするため”make”と検索欄に入力します。
MakerWebhooksがあればそれをクリックします。

![](https://qiita-image-store.s3.amazonaws.com/0/97208/da5a796b-4902-65f9-2d7f-68ab931818e4.png)

MakerWebhooksはEvent単位でトリガーがかかります。今回はEventNameに"Unibo"と入力し”Create trigger”をクリックし作成していきます。
今入力したEventNameはあとでUniboに入力するのでSecretKeyと合わせて覚えておきましょう。

![](https://qiita-image-store.s3.amazonaws.com/0/97208/2628f945-0b77-0b5a-4bf2-b67b6322ca49.png)

次にトリガーが起こった時にしたい動作を選択します。
IFTTTの検索欄でLineを検索し、連携させていきます。
ちなみに、このときにTwitterやGmailなどを選択するとそれと連携させることが出来ます。

![](https://qiita-image-store.s3.amazonaws.com/0/97208/edcb1b20-ba42-31a1-9d82-175120889cc4.png)

Recipientと書かれた欄にメッセージを送るLineのグループを選択します。
Messageと書かれた欄に送信するメッセージを入力を入力します。Value1、Value2などがありプログラムから値を渡すことができます。これを使えば温度センサや明るさセンサーの値をプログラムから渡しメッセージに組み込むことが可能です。
オプションですが写真のURLさえあれば、Lineに写真を投稿することができます。

Create actionをクリックしてメッセージを保存します。

![](https://qiita-image-store.s3.amazonaws.com/0/97208/e3462842-5b7a-7af6-70ac-fc7da6f2b17b.png)


最後にFinishを押し、作成を完了します。

![](https://qiita-image-store.s3.amazonaws.com/0/97208/bc80a16c-47ae-85b5-2524-6a5a8f0b1589.png)



[こちらのリンク](https://ifttt.com/maker_webhooks)をクリックしDocumentationのリンクをクリックします。

![](https://qiita-image-store.s3.amazonaws.com/0/97208/5372deac-65bd-5c73-2208-49d5c9663bae.png)

クリックするとこのような画面に移動します。

このときに表示される赤枠のURLをUniboにコピーします。

![](https://qiita-image-store.s3.amazonaws.com/0/97208/173e8435-3165-7601-3369-2759769cd2a1.png)

## Uniboの準備をする
Uniboのスキルクリエイターに移動し、全体図の章で見せたJSONの文字列をスキルクリエイターにインポートしてください。

インポートが終わったら先ほどIFTTTで取得したURLを張り付けていきます。
http request Nodeをクリックし、赤枠の入力欄に先ほどのURLを貼り付けていきます。この時にURL中央部にある```{event}```は先ほどIFTTTに登録したイベント名に変えておきましょう。
記事の通りに作成している場合はUniboになります。

入力できたら完了を押し作成を完了します。

これでDeployを押し、タイムスタンプのボタンを押せばLineにメッセージが飛ぶような仕組みが完成しました！
![](https://qiita-image-store.s3.amazonaws.com/0/97208/2e4f2f7e-cfc3-fbe8-8a6b-c204c726fc57.png)

余談ですが、functionNodeでhttp request Nodeの応答をUniboでしゃべらすためにメッセージ内容をコピーする処理をいれることでレスポンスをしゃべらすことができるようになります。

![](https://qiita-image-store.s3.amazonaws.com/0/97208/03bfdae6-5813-9d9f-35fa-7b6831d74a01.png)


