# osm-research.cpp
<p>学部・修士レベルの交通データを用いた研究の実装を行うために必要となる最低限のツール一式です. 
あまりにも簡易なので都市の交通シミュレーションなど複雑な処理には不十分ですが, Open Street Mapのデータを使いやすい形に
加工したり, 地図をpngとして可視化したりしてくれたり, 誰でも使うモジュールが一通り入っています.</p>
<p>実装言語はC++11です. 最短経路やビジュアライザなどこのライブラリのすべての機能を利用するためには, C++初級程度の知識が必要となります(クラス、ストリームなど)。ただし, Open Street Mapのデータを加工する部分は, C++を知らなくても実行することが可能なのでそこだけ借りて, 他の言語で研究を進めることも可能です.</p>
<p>Open Street Mapのデータはそのままではなかなか使い物になりません. 主な理由としては, (i)XML形式で不要な情報が大量に入っている, (ii)グラフが非連結である, などがあります. 本ライブラリでは, 頂点の緯度経度, 辺の重み(距離)以外の情報は切り捨て, 連結なグラフの中で頂点数が最大のもの以外は削除するといった処理を行っています. これらの処理は意外と面倒で退屈なので, 本ツールを使ってしまって, 生データのことは忘れてしまうことをオススメします. ちなみに論文では, 生データを加工し圧縮したという点について軽く言及する必要があるかもしれません.</p>



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
    <dd>グラフ全体や, 経路などをpngファイルに可視化する. 色も自由に設定できます.</dd>
    <dt>log.h, log.cpp</dt>
    <dd>デバッグ情報やプログレスバーなどを出力する.</dd>
    <dt>osm_parser.h, osm_parser.cpp</dt>
    <dd>open street mapのRAWデータを変換する処理.</dd>
    <dt>shortest_path.h, shortest_path.cpp</dt>
    <dd>最短経路の計算用. 現状はDijkstraのみ.</dd>
    <dt>commandline.h, commandline.cpp</dt>
    <dd>bashコマンドをC++プログラムから呼び出す用.</dd>
</dl>
