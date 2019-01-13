///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//fps.h
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## ヘッダファイル読み込み ##########
#include<stdio.h>
#include <windows.h>
#include <locale.h>

///########## マクロ定義 ##########

//FPS用のタイマーID
#define TIMER_ID_FPS	100

#define FPS_CALC_AVE	60.0f
#define FPS_DISP		60

///########## 構造体 ##########

//FPSのパラメータ構造体
struct MY_STRUCT_FPS
{
	float		fps_Draw;				//描画するFPS
	DWORD		fps_sta_tm;				//0フレーム目の開始時刻
	DWORD		fps_end_tm;				//設定したフレームの終了時刻
	DWORD		fps_count;				//フレームのカウント
	float		fps_ave = FPS_CALC_AVE;	//FPSを計算するための平均サンプル数
	int			fps_disp = FPS_DISP;	//FPSの値
};

///########## 名前の再定義 ##########

typedef MY_STRUCT_FPS	MY_FPS;

///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
#pragma once	//二重インクルードの防止
///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

///########## グローバル変数 参照の宣言 ##########

///▼▼▼▼▼ 本体はfps.cpp ▼▼▼▼▼

//FPS構造体の変数
extern MY_FPS MyFPS;

///▲▲▲▲▲ 本体はfps.cpp ▲▲▲▲▲

///########## 外部 関数 参照の宣言 ##########

///▼▼▼▼▼ 本体はfps.cpp ▼▼▼▼▼

//画面更新の時刻を取得する関数
extern BOOL MY_FPS_UPDATE(VOID);

//指定したFPSになるように待つ関数
extern VOID MY_FPS_WAIT(VOID);

//FPSの値を表示する関数
extern VOID MY_FPS_DRAW(HDC);

///▲▲▲▲▲ 本体はfps.cpp ▲▲▲▲▲