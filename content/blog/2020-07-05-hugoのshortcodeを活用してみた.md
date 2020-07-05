---
title: HugoのShortcodeを活用してみた
date: 2020-07-05T05:59:12.732Z
description: Hugoにはshortcodeという機能があり簡単な手順で機能を追加できます
tags:
  - hugo
  - shortcode
Categories:
  - hugo
  - shortcode
slug: 2020-07-05-hugo_shortcode
---
下記のサイトを参考にshortcodeをつくってみました。

{{< linkcard "https://nasust.com/hugo/tips/shortcode/">}}

{{< linkcard "https://nasust.com/hugo/shortcode/blogcard/">}}

2つのshortcodeを追加しました。

# warning

警告文を出すようのものですね

{{< warning >}}
各自の環境で同様に動作する保証はありません。
{{< /warning >}}

こんなコードを書いたら、上のようにきれいにしてくれちゃうんです。

```text
{{</* warning */>}}
各自の環境で同様に動作する保証はありません。
{{</* /warning */>}}
```

# link card

リンクですね、リンク先に深い意図はないです。

いい感じに画像が見えたので使わせてもらいました。

{{< linkcard "https://www.zaico.co.jp/">}}


```text
{{</* linkcard "https://www.zaico.co.jp/"*/>}}
```

ちょっとの一工夫でいい感じにできるのはとても便利ですね
