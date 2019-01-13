///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//fps.cpp
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## ヘッダファイル読み込み ##########

#include "fps.h"

///########## グローバル変数の宣言と初期化 ##########

//FPS構造体の変数
MY_FPS MyFPS;

///########## プロトタイプ宣言 ##########

//画面更新の時刻を取得する関数
BOOL MY_FPS_UPDATE(VOID);

//指定したFPSになるように待つ関数
VOID MY_FPS_WAIT(VOID);

///########## 指定したFPSになるように待つ関数 ##########
//引　数：なし
//戻り値：なし
VOID MY_FPS_WAIT(VOID)
{
	//現在の時刻をミリ秒で取得
	DWORD now_tm = GetTickCount();

	//1フレーム目から実際にかかった時間を計算
	DWORD keika_tm = now_tm - MyFPS.fps_sta_tm;

	//待つべき時間 = かかるべき時間 - 実際にかかった時間;
	DWORD wait_tm = (MyFPS.fps_count * 1000 / MyFPS.fps_disp) - (keika_tm);

	//待つべき時間があった場合
	if (wait_tm > 0 && wait_tm < 2000)
	{
		//ミリ秒分、処理を中断する
		Sleep(wait_tm);
	}

	return;
}

///########## 画面更新の時刻を取得する関数 ##########
//引　数：なし
//戻り値：TRUE ：正常終了 / FALSE：異常終了
BOOL MY_FPS_UPDATE(VOID)
{
	//1フレーム目なら時刻を記憶
	if (MyFPS.fps_count == 0)
	{
		//Windowsが起動してから現在までの時刻をミリ秒で取得
		MyFPS.fps_sta_tm = GetTickCount();
	}

	//60フレーム目なら平均を計算する
	if (MyFPS.fps_count == MyFPS.fps_ave)
	{
		//Windowsが起動してから現在までの時刻をミリ秒で取得
		MyFPS.fps_end_tm = GetTickCount();

		//平均的なFPS値を計算
		MyFPS.fps_Show
			= 1000.0f / ((MyFPS.fps_end_tm - MyFPS.fps_sta_tm) / MyFPS.fps_ave);

		//次のFPS計算の準備
		MyFPS.fps_sta_tm = MyFPS.fps_end_tm;

		//カウント初期化
		MyFPS.fps_count = 0;

	}
	MyFPS.fps_count++;

	return true;
}