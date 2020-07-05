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

リンクですね、Notionみたいに横並びにしようか悩みましたが、縦ならびでもよさそうなので、これで。

{{< linkcard "https://wamisnet.github.io/">}}


```text
{{</* linkcard "https://wamisnet.github.io/"*/>}}
```

ちょっとの一工夫でいい感じにできるのはとても便利ですね
