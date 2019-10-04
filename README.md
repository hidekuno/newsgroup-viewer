C++11復習プログラム
=================

## 概要
- 暫くC++に触れていなかったので、簡単なプログラムを実装してみた。
- プログラム内容はnewgroupのリストをツリー表示することである。

## 開発環境
| Item   | Ver. |備考|
|--------|--------|--------|
| OS     | CentOS7 | |
| カーネル | 3.10.0-957.1.3||
| GCC    | 4.8.5||

## ビルド
```
git clone https://github.com/hidekuno/newsgroup-viewer.git
cd newsgroup-viewer
make
```

## 動かし方
```
./newgroup.py > group.txt
./ngv -l < group.txt
```
