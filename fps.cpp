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

//FPSの値を表示する関数
VOID MY_FPS_DRAW(HDC hdc);

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
		MyFPS.fps_Draw
			= 1000.0f / ((MyFPS.fps_end_tm - MyFPS.fps_sta_tm) / MyFPS.fps_ave);

		//次のFPS計算の準備
		MyFPS.fps_sta_tm = MyFPS.fps_end_tm;

		//カウント初期化
		MyFPS.fps_count = 0;

	}
	MyFPS.fps_count++;

	return true;
}

///########## FPSの値を表示する関数 ##########
//引　数：デバイスコンテキストのハンドル
//引　数：なし
VOID MY_FPS_DRAW(HDC hdc)
{
	//FPS値を整形するための変数
	CHAR strfpsChr[64];
	size_t wLen = 0;
	errno_t err = 0;

	//FPS値を整形
	sprintf(strfpsChr, "FPS：%2.1lf", MyFPS.fps_Draw);

	//FPS値を表示するための変数
	TCHAR StrfpsTch[64];

	//ロケール指定
	setlocale(LC_ALL, "japanese");

	//文字列をマルチバイト文字からワイド文字に変換
	err = mbstowcs_s(
		&wLen,				//変換された文字数
		StrfpsTch,			//変換されたワイド文字
		strlen(strfpsChr),	//変換する文字数
		strfpsChr,			//変換するマルチバイト文字
		_TRUNCATE			//バッファに収まるだけの文字列まで変換
	);

	SetBkMode(hdc, TRANSPARENT);			//背景色は上書きしない
	SetTextColor(hdc, RGB(0, 0, 0));		//文字色
	SetBkColor(hdc, RGB(255, 255, 255));	//背景色

	//FPSを描画
	TextOut(hdc, 0, 0, StrfpsTch, lstrlen(StrfpsTch));
}