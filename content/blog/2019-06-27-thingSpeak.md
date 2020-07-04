+++
title = "【IoT可視化ツールレビュー】 thinger.io"
date = 2019-06-27
draft = false
author = "wami"
categories = ["iot","IoT可視化ツールレビュー"]
tags = ["iot","IoT可視化ツールレビュー"]
description = "IoT可視化ツールのレビューを行います"
featured = ""
featuredalt = ""
featuredpath = ""
linktitle = "【IoT可視化ツールレビュー】 thinger.io"
type = "post"

+++


# thinger.io

次の記事が使い方がまとまっていてわかりやすかったです。

http://www.esploradores.com/empezando/hello-world-thinger-io-blink/

## 何を目的としたサービスか

IoTでよくある機能を簡単に試すことができるサービス

データの可視化やデバイスをこのサービス経由のAPIで制御できる

## 何と何ができるのか

### Webやアプリ上でのセンサーデータの可視化（ダッシュボード）

![c05197985d9ee92a9e12aaa71ab7508682bc3fbc.gif](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/1892c54d-c17c-826d-3753-7a5182ad79d8.gif)

### LEDのONOFFやサーボの制御などをWebやアプリ、APIで操作できる

![run.jpg](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/8515c856-3072-c92a-b01c-5e25054dd346.jpeg)
![2019-06-26_16h07_26.png](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/e2bc1576-a039-cdd5-2233-3b58afde14d4.png)


### データ保存機能（バケット）

![IoTBucketData.png](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/fd439a90-c809-a842-459e-9789e65f8888.png)

### エンドポイント機能（デバイスからトリガーがあったときにメールや特定のURLを叩ける）

<img width="726" alt="EmailEndpoint.png" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/ac2fa292-32de-2a6a-40ec-a6d3c68e0bf9.png">


## それがいくらなのか

![2019-06-26_17h21_26.png](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/97208/36c1e5f6-dd5d-d1da-7492-1a71e387aed0.png)

||無料|500円/月|2500円/月|
|:----|:------|:------|:-------|
|接続台数|2台 |20台 |100台|
|ダッシュボード|4|20 |100|
|バケット（何秒に一度データを保存できるか）|60s|30s|15s|
|エンドポイント|4|20|100|

## 使った感じどうだったか

接続するときにひと手間ありそうですが可視化の部分を使用できるとよさそうです。

生のESP32で使用する際にはよいサービスだと思います。

https://github.com/thinger-io/Arduino-Library/tree/master

簡単にダッシュボードがつくれるところもよく、自分でインスタンス立てて制御することもできるようです。
ダッシュボードのレスポンスもよかったです。

https://thinger.io/downloads/
Blynkに似ていますが、アプリのみでなくWebでコントロールできるところが優れています。
