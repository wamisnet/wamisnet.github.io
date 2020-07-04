#!/bin/sh
hugo version
hugo
git clone https://github.com/wamisnet/wamisnet.github.io.git

cp -rp public/* wamisnet.github.io/

cd wamisnet.github.io

git remote set-url origin git@github.com:wamisnet/wamisnet.github.io.git

git config --global user.email "wamiwami@live.jp"
git config --global user.name "wami"

git add --all
git commit -m "Update [ci skip]"
git push origin master
