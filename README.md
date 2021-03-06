# osm-research.cpp
## はじめに
<p>学部・修士レベルの交通データを用いた研究の実装を行うために必要となる最低限のツール一式です. 
あまりにも簡易なので都市の交通シミュレーションなど複雑な処理には不十分ですが, Open Street Mapのデータを使いやすい形に
加工したり, 地図をpngとして可視化したりしてくれたり, 誰でも使うモジュールが一通り入っています.</p>
<p>実装言語はC++11です. 最短経路やビジュアライザなどこのライブラリのすべての機能を利用するためには, C++初級程度の知識が必要となります(クラス、ストリーム、ネームスペースなど)。ただし, Open Street Mapのデータを加工する部分は, C++を知らなくても実行することが可能なのでそこだけ借りて, 他の言語で研究を進めることも可能です.</p>
<p>Open Street Mapのデータはそのままではなかなか使い物になりません. 主な理由としては, (i)XML形式で不要な情報が大量に入っている, (ii)グラフが非連結である, などがあります. 本ライブラリでは, 頂点の緯度経度, 辺の重み(距離)以外の情報は切り捨て, 連結なグラフの中で頂点数が最大のもの以外は削除するといった処理を行っています. これらの処理は意外と面倒で退屈なので, 本ツールを使ってしまって, 生データのことは忘れてしまうことをオススメします. ちなみに論文では, 生データを加工し圧縮したという点について軽く言及する必要があるかもしれません.</p>
<p>2017年現在, 大学から貸与されているMacで特に問題なく動作することを確認しています. もしかしたらビジュアライザで利用しているコンポーネントがインストールされていないかもしれないですが, "tool_Aがありません."と出てくるたびに, ターミナルで`brew install tool_A`してもらえれば大丈夫かと思います.</p>
<p>おそらくかなりバグがあると思いますので見つけたら適宜修正してこの本体を更新してください. また, 自分で実装した, 一般的に用いることができそうなモジュールがあれば是非勝手に追加してください. 特に差し迫って必要になりそうな機能は以下の通りです.

- 緯度・経度を入力として, そこから最も近いグラフ上の頂点をO(logN)で返す機能(Kd Treeなど). タクシーや人のデータをグラフ上の点にマップするのに使います. 現状, 愚直にやってO(N)かかります.
- Dijkstraより速い最短経路計算(Contraction Hierarchyなど). 
- シミュレーション系のコンポーネント(バスや人を１日分, ランダムもしくは指定した通りに動かしてくれる). 
- 時間計測系.
</p>

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
    <dd>ソースコード一式. C++や交通系の基本的なモジュールが入っています. 自分の研究のソースコードもここに書きます. </dd>
    <dt>data</dt>
    <dd>openstreetmapのデータやタクシーのデータなどをいれます.</dd>
    <dt>lib</dt>
    <dd>サードパーティライブラリ. ソースコードが入っているので, srcフォルダのファイルと一緒にビルドされます.</dd>
    <dt>build</dt>
    <dd>ビルドしたオブジェクトなどが置かれます.</dd>
</dl>

## 使い方
`Make list`をすると, デフォルトで実装してるコマンドが見れます.
```
make list
```
`make`でビルド, `make extract_graph ...`でosmデータのパース, `make run`で自分のコードの実行, などがよく使うコマンドになりそうです. これらのコマンドはMakefileやmain.cppで編集できるので適宜追加・変更してもらって構いません.

## 開発の方法
`src/main.cpp`の中に`run`関数があるので, その中で自分の実装を行います. (他のファイルで実装して, ここではそれを呼び出すだけにした方が賢明ですが.)
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
パース後のデータは以下のような構造になっています.
```
頂点数(int) 辺数(int)
最小緯度(double) 最大緯度(double) 最小経度(double) 最大経度(double)
一つ目の頂点の緯度(double) 一つ目の頂点の経度(double)
二つ目の頂点の緯度(double) 二つ目の頂点の経度(double)
.
.
.
最後の頂点の緯度(double) 最後の頂点の経度(double)
一つ目の辺の始点の頂点番号(int) 二つ目の辺の終点の頂点番号(int) 辺の重み(double, メートル)
二つ目の辺の始点の頂点番号(int) 二つ目の辺の終点の頂点番号(int) 辺の重み(double, メートル)
.
.
.
最後の辺の始点の頂点番号(int) 最後の辺の終点の頂点番号(int) 辺の重み(double, メートル)
```
### モジュール一覧
<dl>
    <dt>main.cpp</dt>
    <dd>main関数が入っています.</dd>
    <dt>graph.h, graph.cpp</dt>
    <dd>グラフを表すクラス. 頂点を表す`node.h`や, 辺を表す`edge.h`に依存.</dd>
    <dt>visualizer.h, visualizer.cpp</dt>
    <dd>
	グラフ全体や, 経路などをpngファイルに可視化します. 色も自由に設定できます.
    </dd>
</dl>

```cpp
graph::Graph g("data/graph/processed/sample.txt");
graph::Visualizer vis(g);
graph::Edge e = graph::Edge{0, g.es[0][0], -1};  // 頂点0の一つ目の辺(重みはどうでもよい)
vis.ShowNodesAndEdges("sample.png",  // 出力ファイル名(buildフォルダに生成される)
		      {{0, graph::Visualizer::RED},  //頂点0を赤に塗る
		       {5, graph::Visualizer::BLUE}},  //頂点5を青に塗る
		      {{e, graph::Visualizer::GREEN}});  //辺eを緑に塗る
```

<dl>
    <dd>
    </dd>
    <dt>log.h, log.cpp</dt>
    <dd>デバッグ情報やプログレスバーなどを出力します.</dd>
    <dt>osm_parser.h, osm_parser.cpp</dt>
    <dd>open street mapのRAWデータを変換する処理.</dd>
    <dt>shortest_path.h, shortest_path.cpp</dt>
    <dd>最短経路の計算用. 現状はDijkstraのみ.</dd>
    <dt>commandline.h, commandline.cpp</dt>
    <dd>bashコマンドをC++プログラムから呼び出す用.</dd>
</dl>
