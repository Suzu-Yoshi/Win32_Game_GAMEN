///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//winproc.cpp
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## ヘッダファイル読み込み ##########
#include "main.h"
#include "game.h"

///########## ライブラリ読み込み ##########

///########## マクロ定義 ##########

///########## 列挙型 ##########

///########## 構造体 ##########

///########## 名前の再定義 ##########

///########## グローバル変数の宣言と初期化 ##########

//線の間隔
int GAME_kankaku = 100;

///########## プロトタイプ宣言 ##########

//画面を描画する関数
VOID MY_DRAW_GAME(MY_WIN);

//画面の背景を描画する関数
VOID MY_DRAW_BACKSCREEN(HDC, RECT);

//画面の縦線を描画する関数
VOID MY_DRAW_LINE_TATE(HDC hdc_double, RECT rect);

//画面の横線を描画する関数
VOID MY_DRAW_LINE_YOKO(HDC hdc_double, RECT rect);

///########## 画面を描画する関数 ##########
//引　数：ﾀﾞﾌﾞﾙﾊﾞｯﾌｧﾘﾝｸﾞ用のﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄのﾊﾝﾄﾞﾙ
//戻り値：なし
VOID MY_DRAW_GAME(MY_WIN mywin)
{
	//背景を描画する
	MY_DRAW_BACKSCREEN(mywin.hdc_double, mywin.win_rect_cli);

	//画面の縦線を描画する
	MY_DRAW_LINE_TATE(mywin.hdc_double, mywin.win_rect_cli);

	//画面の横線を描画する
	MY_DRAW_LINE_YOKO(mywin.hdc_double, mywin.win_rect_cli);

	//

}

///########## 画面の背景を描画する関数 ##########
//引　数：ﾀﾞﾌﾞﾙﾊﾞｯﾌｧﾘﾝｸﾞ用のﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄのﾊﾝﾄﾞﾙ
//引　数：クライアント領域
//戻り値：なし
VOID MY_DRAW_BACKSCREEN(HDC hdc_double, RECT rect)
{
	//ブラシを作成
	HBRUSH hbrush = CreateSolidBrush(RGB(0, 255, 0));

	//ブラシを設定
	SelectObject(hdc_double, hbrush);

	//四角を描画
	Rectangle(
		hdc_double,		//デバイスコンテキストのハンドル
		rect.left,		//四角の左上のX座標
		rect.top,		//四角の左上のY座標
		rect.right,		//四角の右下のX座標
		rect.bottom);	//四角の右下のY座標

	//ブラシを削除
	DeleteObject(hbrush);

}

///########## 画面の縦線を描画する関数 ##########
//引　数：ﾀﾞﾌﾞﾙﾊﾞｯﾌｧﾘﾝｸﾞ用のﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄのﾊﾝﾄﾞﾙ
//引　数：クライアント領域
//戻り値：なし
VOID MY_DRAW_LINE_TATE(HDC hdc_double, RECT rect)
{
	//ループで使用
	int loop = 0;

	//線を描く最大数
	int Draw_Line_MAX = rect.right / GAME_kankaku;

	//線の描き始め位置
	POINT pt_Start;
	pt_Start.x = rect.left;
	pt_Start.y = rect.top;

	//線の描き終わり位置
	POINT pt_End;
	pt_End.x = rect.left;
	pt_End.y = rect.bottom;

	//ペン：線を引く色、太さなどを設定
	HPEN hpen;

	//ペンを作成
	hpen = CreatePen(
		PS_SOLID,				//ペンのタイプ
		3,						//ペンの太さ
		RGB(0, 0, 0));	//ペンの色

	//ペンを設定
	SelectObject(hdc_double, hpen);

	for (loop = 0; loop < Draw_Line_MAX; loop++)
	{

		//線の描き始め位置
		MoveToEx(
			hdc_double,							//デバイスコンテキストのハンドル
			pt_Start.x + loop* GAME_kankaku,	//描き始めるX座標
			pt_Start.y,							//描き始めるY座標
			NULL);								//以前のカレントポジション/必要ないならNULL

		//線を描く(斜め棒)
		LineTo(
			hdc_double,						//デバイスコンテキストのハンドル
			pt_End.x + loop * GAME_kankaku,	//描き終わるX座標
			pt_End.y);						//描き終わるY座標
	}

	//ブラシを削除
	DeleteObject(hpen);
}

///########## 画面の横線を描画する関数 ##########
//引　数：ﾀﾞﾌﾞﾙﾊﾞｯﾌｧﾘﾝｸﾞ用のﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄのﾊﾝﾄﾞﾙ
//引　数：クライアント領域
//戻り値：なし
VOID MY_DRAW_LINE_YOKO(HDC hdc_double, RECT rect)
{
	//ループで使用
	int loop = 0;

	//線を描く最大数
	int Draw_Line_MAX = rect.bottom / GAME_kankaku;

	//線の描き始め位置
	POINT pt_Start;
	pt_Start.x = rect.left;
	pt_Start.y = rect.top;

	//線の描き終わり位置
	POINT pt_End;
	pt_End.x = rect.right;
	pt_End.y = rect.top;

	//ペン：線を引く色、太さなどを設定
	HPEN hpen;

	//ペンを作成
	hpen = CreatePen(
		PS_SOLID,				//ペンのタイプ
		3,						//ペンの太さ
		RGB(0, 0, 0));	//ペンの色

	//ペンを設定
	SelectObject(hdc_double, hpen);

	for (loop = 0; loop < Draw_Line_MAX; loop++)
	{

		//線の描き始め位置
		MoveToEx(
			hdc_double,							//デバイスコンテキストのハンドル
			pt_Start.x ,						//描き始めるX座標
			pt_Start.y + loop * GAME_kankaku,	//描き始めるY座標
			NULL);								//以前のカレントポジション/必要ないならNULL

		//線を描く(斜め棒)
		LineTo(
			hdc_double,							//デバイスコンテキストのハンドル
			pt_End.x ,							//描き終わるX座標
			pt_End.y + loop * GAME_kankaku);	//描き終わるY座標
	}

	//ブラシを削除
	DeleteObject(hpen);
}