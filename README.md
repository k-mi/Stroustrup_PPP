『ストラウストラップのプログラミング入門』の練習問題  
--------
[『ストラウストラップのプログラミング入門ーC++によるプログラミングの原則と実践ー』](http://www.shoeisha.co.jp/book/detail/9784798119595)の練習問題です。  
Exercises from "Programming &ndash; Principles and Practice Using C++" by Stroustrup (1st, Japanese translation).  
  
  
#### 環境
主にOS X上のGCC 5.2.0で確認を行っています。   
また、12章以降に出てくるGUIのプログラムについてはFLTKが必要となりますが、こちらはバージョン1.3.3を使用し、Visual C++ 2015で確認を行っています。

hash_mapが使用されていた初版ではなく、原著第2版の[std_lib_facilities.h](http://www.stroustrup.com/Programming/PPP2code/std_lib_facilities.h)を使用しています。
また、regexやarrayなどのC++11から標準ライブラリに取り入れられたものに関しては、Boostを使用していません。
そのため、C++11を有効にするコンパイラオプションが必要かもしれません。
  
  
#### ファイル名について  
+ 本文中のサンプル:　"章番号"\_"節番号"\_"節の通し番号".cpp （例）2\_2\_1.cpp  
+ TRY THIS:　"章番号"\_"節番号"\_try"節の通し番号".cpp （例）3\_3\_try1.cpp  
+ ドリル:　drill"章番号"\_"問題番号".cpp （例）drill3\_1.cpp  
+ 練習問題:　q"章番号"\_"問題番号".cpp （例）q2\_1.cpp  
+ 入力/出力ファイル:　ソースコード内で指定がなければ、拡張子の前に\_inputや\_outputと付いたものを使用
