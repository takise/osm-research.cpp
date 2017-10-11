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
<dl>
    <dt>src</dt>
    <dd>ソースコード一式. C++や交通系の基本的なモジュールが入っている. 自分の研究のソースコードもここに書く. </dd>
    <dt>data</dt>
    <dd>openstreetmapのデータやタクシーのデータなどをいれる.</dd>
    <dt>lib</dt>
    <dd>サードパーティライブラリ. ソースコードが入っているので, srcフォルダのファイルと一緒にビルドされる.</dd>
</dl>

## 使い方
`Make list`をすると, デフォルトで実装してるコマンドが見れます.
```
make list
```
`make`でビルド, `make extract_graph ...`でosmデータのパース, `make run`で自分のコードの実行, などがよく使うコマンドになりそう.

## 開発の方法
`src/main.cpp`の中に`run`関数があるので, その中で自分の実装を行います.
```cpp
void run(int argc, char *argv[]) {
    std::cout << "Hello World!" << std::endl;
    /*
    Implement your own research here!
   */
}
```
`make extract_graph`でパースしたデータは`Graph.cpp`の`Graph`クラスで読み込んで使うことができます.
```cpp
graph::Graph graph("data/graph/processed/tokyo.txt");

graph.es[0][1] // 頂点0の2つめの辺
graph.w[3][2]  // 頂点3の3つめの辺の重み
graph.lat[0]   // 頂点0の緯度
```
### モジュール一覧
<dl>
    <dt>main.cpp</dt>
    <dd>main関数が入っている.</dd>
    <dt>graph.h, graph.cpp</dt>
    <dd>グラフを表すクラス. 頂点を表す`node.h`や, 辺を表す`edge.h`に依存.</dd>
    <dt>visualizer.h, visualizer.cpp</dt>
    <dd>グラフ全体や, 経路などをpngファイルに可視化する.</dd>
</dl>
