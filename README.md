
ツリー表示ツール
=================

## 概要
- 暫くC++に触れていなかったので、簡単なツールを実装してみた。
- 階層化された名前のテキストデータをツリー表示する。

## 開発環境
| Item   | Ver. |備考|
|--------|--------|--------|
| OS     | Ubuntu 18.04.5 LTS | |
| GCC    | 9.3.0||
| CPU    | Intel(R) Core(TM) i7-10510U CPU @ 1.80GHz|

## 開発ツールのインストール
ubuntu
```
sudo apt-get update
sudo apt-get install g++ autoconf make git
sudo apt-get install libsparsehash-dev
```
mac
```
brew install autoconf
brew install google-sparsehash
```

## ビルド
```
git clone https://github.com/hidekuno/tree-viewer.git
cd tree-viewer
autoconf
./configure
make
```

## 動かし方
```
./newsgroup.py| | ^gmane\. | ./treeview -l
./newsgroup.py| | ^gwene\. | ./treeview -l
```
<img src="https://user-images.githubusercontent.com/22115777/66184854-64bd2880-e6b8-11e9-863e-867540098065.png" width=50%>
