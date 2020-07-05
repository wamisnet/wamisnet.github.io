#!/bin/sh

sudo apt-get install nodejs npm
cd node
npm i
node index.js &
sleep 10
cd ..

git submodule init
git submodule update

hugo version

hugo
git clone https://github.com/wamisnet/wamisnet.github.io.git

cp -rp public/* wamisnet.github.io/

cd wamisnet.github.io

git remote set-url origin git@github.com:wamisnet/wamisnet.github.io.git

git config --global user.email "wamiwami@live.jp"
git config --global user.name "wami"

git add --all
git commit -m "Update Site"
git push origin master
