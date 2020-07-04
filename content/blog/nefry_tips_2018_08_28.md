+++
title = "Nefry Tips 無線LAN接続について"
date = 2018-08-28
draft = false
author = "wami"
categories = ["Nefry","無線LAN"]
tags = ["Nefry","無線LAN"]
description = "NefryのTips紹介します！今回は無線LANのプチTips"
featured = ""
featuredalt = ""
featuredpath = ""
linktitle = "Nefry Tips 無線LAN接続について"
type = "post"

+++


Nefryを使ったいろんな作品が見られて幸せなわみさんです。

今回は無線LANのプチTipsを共有したいと思っています。

Nefryには、Webページ上で設定した無線LANから自動的にもっとも電波強度が強いものに接続するような機能があります。

ただ、基本的には起動時に接続しにいくのみで、起動したあとに切断された場合再接続処理が上手くいかず接続できないことがあります。

デモのような短時間の動作であれば上記のような現象は気にならないと思いますが、長時間のモニタリングなどでなってしまうとなかなか辛いことがあると思いますので今回のTipsを試してもらえればと思います！

{{< highlight c >}}
#include<Nefry.h>
void setup() {
  // 何か処理
}

void loop() {
  // なんか処理a
  if(WiFi.status() != WL_CONNECTED){
    //無線LANが接続されていないとき
    Nefry.reset();
  }
}
{{< / highlight >}}

上記のコードが今回のTipsです。

無線LANに接続していないときにNefryをリセットするコードになります。

Nefryがネットワークにつながらなくなっても再起動して無線LAN接続が正常に行えるはずです！！

ぜひ試してみてください！
