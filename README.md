
ツリー表示ツール
=================

## 概要
- 暫くC++に触れていなかったので、簡単なツールを実装してみた。
- 階層化された名前のテキストデータをツリー表示する。

## 開発環境
| Item   | Ver. |備考|
|--------|--------|--------|
| OS     | CentOS7 | |
| GCC    | 4.8.5||
| CPU    | Intel(R) Core(TM) i3-2120 CPU @ 3.30GHz |

## ビルド
```
git clone https://github.com/hidekuno/tree-viewer.git
cd tree-viewer
make
```

## google sparsehashのインストール
ubuntu
```
sudo apt-get install libsparsehash-dev
```
centos
```
sudo yum install sparsehash-devel
```
mac
```
brew install google-sparsehash
```

## ビルド
```
git clone https://github.com/hidekuno/tree-viewer.git
cd tree-viewer
make
```
## 動かし方
```
./newsgroup.py| ./treeview -l
```
<img src="https://user-images.githubusercontent.com/22115777/66184854-64bd2880-e6b8-11e9-863e-867540098065.png" width=50%>
