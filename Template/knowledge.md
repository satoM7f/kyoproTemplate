# 日々の競プロで得た知見

## 分かってないこと

- DP
- 参照渡し

## 教訓

- 基本 long long 型を使う
  - 大きい値（$10^9$等）が条件にあった場合は特に気を付ける
  - INF でなく LINF

- 「l」（Lの小文字）は変数等に使用しない
  - 「l」「1」がフォントによっては見分けがつかず，デバッグの邪魔

- 問題の意味が分からなかったら，とりあえずノートやホワイトボードに色々書いてみる

- やり方はあってるはずなのに WA の時確認すること
  - 不等号の向き・＝を入れるか入れないか
  - デバッグprint消してない
  - コピペでミスってる
  - 提出する問題・言語の指定が間違っている
  - 普通にやり方が間違っている

- **まず全探索より始めよ**
  - 「なんか工夫したら奇麗に書けるのでは？」という心境にしてくる「全探索を使わないで解ける俺かっこいいトラップ問題」がある（ABC333Cなど）
  - 可能なループ回数は大体$10^9$程度まで
    - 基本$10^8$程度までと考えておく，$10^10$は完全に無理
  - 二，三重ループが間に合わないなら工夫して一，二重ループにできないか工夫する
  - 範囲を絞った全探索も考えてみよ

- **負の数のmodは負の数**
  - `-5 % 2` は `-1`

## 教訓から導いた問題を解くフロー

0. 問題・制約を見て，全く分からないなら別の問題へ
1. まず，制約から**全探索**が可能か考察
    - 具体的には多重ループ等で解集合を全列挙できるか（ABC333Cなど）
2. 全列挙無理ならアルゴリズムを考える

## プログラムのテクニック

### ◆  ソート

#### 昇順（小さい順）にソート  

- `sort(all(v));`

#### 降順（大きい順）にソート  

- rallを使う
  ```cpp
  // #define rall(v) (v).rbegin(), v.rend()
  sort(rall(vec));
  ```
- ソート前にマイナスをかけて昇順にソートした後マイナスをかけて戻す
  ```cpp
  rep(i, vec.size()) vec[i] *= -1;
  sort(all(vec));
  rep(i, vec.size()) vec[i] *= -1;
  ```

#### `vector<pair<ll, ll>>` を first でソート  

- ```cpp
  vp vecpr = {{3,43},{1,53},{9,22}};
  sort(all(vecpr));
  ```
  ※pairのfirstでソートされることに注意

#### `vector<pair<ll, string>>` first を降順，first が同じなら second で昇順でソート
- ```cpp
  // 比較関数
  bool my_compare(pair<ll, string> a, pair<ll, string> b){
      // 基本はfirstで比較
      if(a.first != b.first){
          // return a.first < b.first; // 昇順
          return a.first > b.first; // 降順
      }
      // それ以外はsecondで比較
      if(a.second != b.second){
          return a.second < b.second; // ABC順
          // return a.second > b.second; // CBA順
      }else return true; // どちらも同じ
  }
  sort(vec.begin(), vec.end(), my_compare);
  ```

### ◆ vector ・ string

#### vectorでの二次元配列の初期化

- ```cpp
  vector<vector<int>> data(3, vector<int>(4));
  ```

#### vector / string の特定の要素をカウントする

- ```cpp
  count(all(s), 'o')
  ```

#### string のスライス 

- ```cpp
  string s = "apple";
  out(s.substr(1, 3)); // ppl
  out(s.substr(1)); // pple
  ```
  ※s.substr()でsが書き換わるわけではない  
  　あくまで条件にあう文字列を返すだけ

#### vector の最大値・最小値  

- ```cpp
  vl vec = {4,1,-2,3};
  out(*max_element(all(vec))); // 4
  out(*min_element(all(vec))); // -2
  ```

- ```cpp
  out(max({4,1,-2,3})); //4
  out(min({4,1,-2,3})); //-2
  ```
  ※`max(vec)`はコンパイルエラー

#### mapについて

- map型は辞書型  
  Pythonのdictと考えると分かりやすい  
  ```cpp
  map<string, ll> dic;
  dic["JP"] = 127;
  dic["KR"] = 12;
  dic["ID"] = 7;
  dic.erase("JP"); //{"JP",127}が消される
  ```
  mapは内部で平衡二分木を使っており，keyでソート済データとして持っている．  
  要素の検索はvectorに比べ速く，オーダーはO(logN)．  
  **※検索早くしたいだけ，ソートされてなくてよい場合`unordered_map`を使うべき**

#### vector を使った map(辞書型)の作り方

- pair に (key, value) を入れる  
  ```cpp
  vector<pair<ll, ll>>
  ```
  やってることはunordered_mapと同じ

### ◆ 浮動小数点の丸め込み

浮動小数点型（double, float）を整数型（int, ll）に丸める

#### 正の無限大への丸め込み

- `std::ceil(-2.5) //-2`

#### 負の無限大への丸め込み

- `std::floor(-2.5) //-3`

#### 0 方向への丸め込み（小数点以下の情報を隠滅する）

- `(ll)-5.0 / (ll)2.0 //-2`  
（ただ割るだけ）

#### .4は絶対値が小さくなる方向へ，.5は絶対値が大きくなる方向への丸め込み

- `std::round(-2.5) //-3`

#### 最近接偶数への丸め込み（.5は一番近い偶数にする）

- `std::nearbyint(-2.5) //-2`

### ◆ おしゃれな書き方

- `if(ans < x) ans = x;` ではなく  
`ans = max(ans, x);` の方がかっこいい

### 文字列長を固定して表示

- ```
  for(i = 7; i < 13; i++){
    cout << setw(2) << ",";
  }
  // "7, 8, 9,10,11,12"
  ```

## データ構造

- Union Find
- 優先度付きキュー
- セグラメント木

## アルゴリズム

### ◆ DFS

- visited（各頂点の訪問状態）とdeque（スタック）を初期化
- 初期ノードをスタックに追加し、スタックが空になるまでループを実行
  - スタックから頂点を取り出す
  - 取り出した頂点が訪問済みでない場合は訪問済みに設定
  - 隣接する未訪問の頂点をスタックに追加

### ◆ BFS

- visited（各頂点の訪問状態）とdeque（キュー）を初期化
- 初期ノードをキューに追加し、訪問済みに設定
- キューが空になるまでループを実行
  - キューから頂点を取り出す
  - 隣接する未訪問の頂点をキューに追加し，訪問済みに設定


### ◆ 尺取り法
### ◆ DP
### ◆ 二分探索 ←忘れがち
### ◆ 全探索 ←忘れがち
