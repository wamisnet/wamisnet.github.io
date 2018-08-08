#!/bin/sh

go get -v github.com/spf13/hugo
hugo
git clone https://github.com/wamisnet/wamisnet.github.io.git
ls
cp public/ wamisnet.github.io/

cd wamisnet.github.io
ls
git remote set-url origin git@github.com:wamisnet/wamisnet.github.io.git

git config --global user.email "wamiwami@live.jp"
git config --global user.name "wami"

git add --all
git commit -m "[auto] commit LibraryDocument"
git push origin master
