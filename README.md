# osm-research.cpp
Lightweight, flexible C++ Framework to import, load and analyze Open Street Map data.

## インストール
レポジトリをcloneして, プロジェクトのルートフォルダに移動, makeするとビルドできます.
```
git clone https://github.com/takise/osm-research.cpp.git
cd osm-research.cpp
make
```
ビルドに成功すると以下が表示されます.
```
Compilation succeeded!
```
もしくは
```
make: `build' is up to date.
```
## フォルダ構成
- src
プログラムのソースコード
- data
openstreetmapのデータなど
- lib
サードパーティライブラリ

## 使い方
```
make list
```

### Convert .osm data to simpler format
##### .osm format
```xml
<?xml version="1.0" encoding="UTF-8"?>
<osm ... >
 <bounds minlat="35.0069900" minlon="135.7676900" ... >
 <node id="434344368" ... />
 <node id="434344373" ... />
 <way id="205862738" ... >
  <nd ref="2158461253"/>
  ...
  <nd ref="2158461253"/>
  <tag k="source" v="Bing"/>
 </way>
</osm>
```
##### output format (light and easy to handle)
```
69 148 // number of nodes and edges
35.0027689209 35.0097928772 135.7662576904 135.7714620361 // bounds
35.0037803650 135.7693176270 // lat and lon of the first node
...
0 65 28.8085830773 // nodes connected by and weight of the first edge
```
### Calculate shortest paths, nearest neighbors, and many others easily
##### Shortest Path
Dijkstra, Contraction Hierarchy and  Hub-Labeling are implemented.
##### Nearest Neighbor
kdTree, which is simple but fast algorithm for NN is implemented.
### Visualize any road networks in various format
Highlight any nodes and edges in various colors you want.
  
## How to use

## License
