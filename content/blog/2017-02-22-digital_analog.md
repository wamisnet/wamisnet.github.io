+++
title = "デジタル、アナログ　説明資料"
date = 2017-02-22
draft = false
author = "wami"
categories = ["説明資料"]
tags = ["説明資料"]
description = "デジタル、アナログ　説明資料"
featured = ""
featuredalt = ""
featuredpath = ""
linktitle = "デジタル、アナログ　説明資料"
type = "post"

+++

アナログ、デジタルと聞いて何が思い浮かぶでしょうか？

テレビもありますが、今回は電気的にデジタル、アナログの違いについて説明していきます。

# アナログデジタルの違いって？

一番の違いはグラフにしたときに分かります。
これは電圧の変化のことを指します。

デジタルはある(1)ない(0)のどちらかでの表現のためシンプルなデータになっています。
これによってあるかないかはハッキリと見て分かるのですがもともとの値がどれくらい大きかったのか、小さかったのかは分からなくなってしまいました。

アナログであればどれだけ大きい、小さいのかは分かるのですがデータとしては大きいという状態になります。

# マイコンでみるアナログ、デジタル

アナログ、デジタルがどの様なものか分かったところで、マイコン（Arduinoなど）でその値を取得する方法を説明します。

マイコンの種類により詳細な手順は変わるので注意してください。

アナログ、デジタルの入出力については、指定されたピンでやりとりします。

今回のプログラムについての説明は全てArduino Unoを対象にさせていただきます。


## デジタル

### 入力

Arduino Unoで例えるとdigitalRead関数により、ある(HIGH)ない(LOW)を取得できます。
このときに注意しないといけないのが閾値の値です。

Arduino Unoの場合、閾値は2.5v以上になるとHIGHになり、それ以下はLOWとなります。この閾値はマイコンより異なるので注意が必要です。

スイッチなどを付けて、押された押されてないという状態を取得する場合、ノイズによって押していないのに押したと誤検知することがあります。
その時にはプルアップという方法をすることで誤検知を減らすことができます。

### 出力

Arduino Unoで例えるとdigitalWrite関数により、ある(HIGH)ない(LOW)を出力できます。

Arduino UnoではHIGHのとき5vが出力され、LOWのとき0vが出力されます。

## アナログ

### 入力

Arduino Unoで例えるとanalogRead関数により、0(0v)-1023(5v)の1024段階で値を取得できます。

入力する電圧が5vを超える場合、抵抗で分圧をすることで入力することができます。

分圧については、検索していただくと計算してくれるサイトなどあるので参考にしてください。

### 出力

Arduino Unoではアナログ出力はできません。
しかしPWMと呼ばれる方式により、擬似的にアナログ出力をすることができます。　

PWMの出力方法はanalogWrite関数により可能となります。0(0v)-255(5v)の256段階で指定することが可能です。

それによりLEDをふんわり付けたりすることが可能です。

