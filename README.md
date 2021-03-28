
Tree view tool
=================

## Overview
- Implemented a simple tool on the C++.
- Display text data with hierarchical names in a tree.

## Development
| Item   | Ver. |
|--------|--------|
| OS     | Ubuntu 18.04.5 LTS |
| GCC    | 9.3.0|
| CPU    | Intel(R) Core(TM) i7-10510U CPU @ 1.80GHz|

## Installation of development tools
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

## Build
```
git clone https://github.com/hidekuno/tree-viewer.git
cd tree-viewer
autoconf
./configure
make
```

## Run(ex.)
```
./newsgroup.py| ./treeview -l
```
<img src="https://user-images.githubusercontent.com/22115777/66184854-64bd2880-e6b8-11e9-863e-867540098065.png" width=50%>

```
ls -R .git|grep ':$' |sed -e 's/.$//' | ./treeview -d / -m
```
<img src="https://user-images.githubusercontent.com/22115777/112082901-74407200-8bc9-11eb-9ced-d6444858d20e.png" width=30%>
