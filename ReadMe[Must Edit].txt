▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
◎このプログラムが提供していること
　＆関連するプログラムファイル

・ウィンドウの作成、表示
　・main.h
　・main.cpp
・メッセージの取得
　・winproc.h
　・winproc.cpp
・FPSの設定・表示
　※以前はタイマーの中でFPSの設定をしていたが、
　　タイマー内でSleep関数を使用すると、
　　Sleepで処理が停止している際に、次のタイマーのメッセージが
　　メッセージキューに入るため、一つの処理を正しく終了できない可能性がある
　　そのため、タイマー内でSleep関数を使用しないプログラムに変更した
　・fps.h
　・fps.cpp
　・main.cpp
・ダブルバッファリングの設定
　・main.h
　・main.cpp
　・winproc.h
　・winproc.cpp
・ウィンドウの終了
　・winproc.h
　・winproc.cpp

▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

※おすすめ？サイト
◎色をRGB値で調べたいとき
https://www.colordic.org/