main.c
  a.exe dat1_in.txt answer.txt でdat1_inから入力しanswerに出力
  文字列が短い順にソートし、BM法のずらし表と文字数をもつtext構造体を作成
    (BM法はhttps://algoful.com/Archive/Algorithm/BMSearch参照)
  limit文字以上の分割文字列について、BM法で一致したところ全てにその文字列を配置
    →短い方から走査するので一致するところが少ない(→一致するところが正解の確率が高い)長い文字列を後から上書き
   
  ex)
           axcaxxdbcxd について
    ab     ab aab   
    bd     ab abbd  bd
    cad    abcacad cad
    cdbc   abcaccdbcad
    正解   abcadcdbcbd  (9/11=82%)
    
    
distance.c
  a.exe answer.txt dat1_ref.txt で編集距離を計算
  40万×40万=1600億の配列が取れないので2列を使いまわしてメモリ使用量削減
  (1600億回比較するのは変わらないので20分くらいかかります...)
  

sys/time.h と sys/resource.h が使えなかったので template.c 参考に修正お願いします
上書きしただけなので効率いい方法ほかにあるかも
dat0では2分くらいで85%でした、編集距離長すぎるからなかなか試せない
