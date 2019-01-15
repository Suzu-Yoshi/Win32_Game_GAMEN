///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//main.cpp
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## ヘッダファイル読み込み ##########
#include "main.h"
#include "fps.h"
#include "winproc.h"

///########## ライブラリ読み込み ##########

///########## マクロ定義 ##########

///########## 列挙型 ##########

///########## 構造体 ##########

///########## 名前の再定義 ##########

///########## グローバル変数の宣言と初期化 ##########

//自作ウィンドウ構造体の変数
MY_WIN MyWin;

///########## プロトタイプ宣言 ##########

//ウィンドウを生成する
BOOL MY_CreateWindowClass(HINSTANCE);

//自分のウィンドウクラスを作成、登録する関数
BOOL MY_CreateWindow(HINSTANCE);

//クライアント領域を設定する
VOID MY_SetClientSize(VOID);

//ダブルバッファリングの設定をする
VOID MY_SetDoubleBufferring(VOID);

///########## メイン関数 ##########
//引　数：アプリケーションのインスタンスハンドル
//引　数：アプリケーションの前のインスタンスハンドル(Win32は常にNULL)
//引　数：コマンドライン引数の文字列
//引　数：ウィンドウの表示状態
//戻り値：メッセージ内wParam
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nCmdShow)
{

	//終了チェック
	BOOL CheckError;

	//自分のウィンドウクラスを作成、登録する関数
	CheckError = FALSE;		//チェック初期化
	CheckError = MY_CreateWindowClass(hInstance);

	//登録ができなかったらプログラムを終了する
	if (CheckError == FALSE) { return -1; }

	//ウィンドウを生成する(サイズ変更なし)
	MyWin.win_mode = (int)WIN_RESZ_NG;	//ウィンドウ表示モードを設定
	CheckError = FALSE;					//チェック初期化
	CheckError = MY_CreateWindow(hInstance);

	//ウィンドウが生成されなかったらプログラムを終了する
	if (MyWin.hwnd == NULL) { return -1; }

	//クライアント領域を再設定する
	MY_SetClientSize();

	//ダブルバッファリングの設定をする
	MY_SetDoubleBufferring();

	//ウィンドウを表示
	ShowWindow(MyWin.hwnd, SW_SHOW);

	/*
	//ウィンドウクラスを登録できなかったとき
	if (!RegisterClass(&MyWin.winc))
	{
		//メッセージボックスを表示
		MessageBox(NULL, ERR_MSG_NO_WIN_CLASS, ERR_MSG_TITLE, MB_OK);

		return FALSE;
	}*/

	//無限ループ
	while (true)
	{
		//メッセージが「メッセージキュー」にあるか判断する
		if (PeekMessage(&MyWin.msg, NULL, 0, 0, PM_REMOVE))
		{
			//メッセージが「メッセージキュー」にあるとき

			//閉じるボタンを押したときは無限ループから抜ける
			if (MyWin.msg.message == WM_QUIT)
			{
				break;
			}

			//仮想キーコードを実際の文字に変換する
			TranslateMessage(&MyWin.msg);

			//メッセージをウィンドウプロシージャに送る
			DispatchMessage(&MyWin.msg);
		}
		else
		{
			//メッセージが「メッセージキュー」にないとき

			//時間取得
			MY_FPS_UPDATE();

			//WM_PAINTを発生
			InvalidateRect(MyWin.hwnd, NULL, FALSE);

			//指定したFPSになるように待つ
			MY_FPS_WAIT();
		}
	}

	return (int)MyWin.msg.wParam;
}

///########## 自分のウィンドウクラスを作成、登録する関数 ##########
//引　数：メイン関数のインスタンスハンドル
//戻り値：TRUE ：正常終了 / FALSE：異常終了
BOOL MY_CreateWindowClass(HINSTANCE hInstance)
{
	//ブラシを作成
	HBRUSH brush;

	//ブラシの色を設定
	brush = CreateSolidBrush(RGB(255, 255, 255));

	//ウィンドウクラスの設定はここから
	MyWin.winc.style = CS_HREDRAW | CS_VREDRAW;
	MyWin.winc.lpfnWndProc = MY_WndProc;			//自作のウィンドウプロシージャ
	MyWin.winc.cbClsExtra = 0;
	MyWin.winc.cbWndExtra = 0;
	MyWin.winc.hInstance = hInstance;				//メイン関数のインスタンスハンドル
	MyWin.winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	MyWin.winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	MyWin.winc.hbrBackground = brush;				//ブラシの色を設定
	MyWin.winc.lpszMenuName = NULL;
	MyWin.winc.lpszClassName = TEXT(MY_WIN_CLASS);	//自作のウィンドウクラスの名前

	//ブラシを削除
	DeleteObject(brush);

	//ウィンドウクラスを登録できなかったとき
	if (!RegisterClass(&MyWin.winc))
	{
		//メッセージボックスを表示
		MessageBox(NULL, ERR_MSG_NO_WIN_CLASS, ERR_MSG_TITLE, MB_OK);

		return FALSE;
	}

	return TRUE;
}

///########## ウィンドウを生成する関数 ##########
//引　数：メイン関数のインスタンスハンドル
//戻り値：TRUE ：正常終了 / FALSE：異常終了
BOOL MY_CreateWindow(HINSTANCE hInstance)
{
	switch (MyWin.win_mode)
	{
	case WIN_RESZ_OK:
		//ウィンドウのサイズ変更ができる

		//ウィンドウを作成する
		MyWin.hwnd = CreateWindow(
			TEXT(MY_WIN_CLASS),
			TEXT(GAME_TITLE),
			WS_OVERLAPPEDWINDOW,
			GAME_LEFT,
			GAME_TOP,
			GAME_RIGHT,
			GAME_BOTTOM,
			NULL,
			NULL,
			hInstance,
			NULL);
		break;

	case WIN_RESZ_NG:
		//ウィンドウのサイズ変更ができない

		//ウィンドウを作成する
		MyWin.hwnd = CreateWindow(
			TEXT(MY_WIN_CLASS),
			TEXT(GAME_TITLE),
			WS_STATIC_WINDOW,
			GAME_LEFT,
			GAME_TOP,
			GAME_RIGHT,
			GAME_BOTTOM,
			NULL,
			NULL,
			hInstance,
			NULL);
		break;

	case WIN_NO_TITLE:
		//ウィンドウのタイトルを表示しない

		//ウィンドウを作成する
		MyWin.hwnd = CreateWindow(
			TEXT(MY_WIN_CLASS),
			TEXT(GAME_TITLE),
			WS_NOT_TITLE,
			GAME_LEFT,
			GAME_TOP,
			GAME_RIGHT,
			GAME_BOTTOM,
			NULL,
			NULL,
			hInstance,
			NULL);
		break;
	}

	//ウィンドウが生成されなかったとき
	if (MyWin.hwnd == NULL)
	{
		//メッセージボックスを表示
		MessageBox(NULL, ERR_MSG_NO_WIN_CREATE, ERR_MSG_TITLE, MB_OK);

		return FALSE;
	}

	return TRUE;
}

///########## クライアント領域の設定をする関数 ##########
//引　数：なし
//戻り値：なし
VOID MY_SetClientSize(VOID)
{
	//画面の表示領域を調整する構造体
	RECT rect_set;

	//最初のクライアントの領域を設定
	rect_set.top = GAME_TOP;
	rect_set.left = GAME_LEFT;
	rect_set.bottom = GAME_BOTTOM;
	rect_set.right = GAME_RIGHT;

	//デスクトップの大きさを取得する構造体
	RECT Desktop_rect;

	//デスクトップのワークエリア領域を取得
	SystemParametersInfo(SPI_GETWORKAREA, 0, &Desktop_rect, 0);

	//ウィンドウを画面中央に表示するとき使用
	int Client_width_half;
	int Client_height_half;
	int Desktop_width_half;
	int Desktop_height_half;

	//ウィンドウ領域を取得
	GetWindowRect(MyWin.hwnd, &MyWin.win_rect_win);

	//クライアント領域を取得
	GetClientRect(MyWin.hwnd, &MyWin.win_rect_cli);

	//クライアント領域の幅を修正
	rect_set.right += (
		(MyWin.win_rect_win.right - MyWin.win_rect_win.left)	// (ウインドウ  の横サイズ) 
		- (MyWin.win_rect_cli.right - MyWin.win_rect_cli.left)	//-(クライアントの横サイズ)
		);

	//クライアント領域の高さを修正
	rect_set.bottom += (
		(MyWin.win_rect_win.bottom - MyWin.win_rect_win.top)	// (ウインドウ  の縦サイズ)
		- (MyWin.win_rect_cli.bottom - MyWin.win_rect_cli.top)	//-(クライアントの縦サイズ)
		);

	//ウィンドウを画面中央に表示

	//デスクトップ領域の幅の半分の値を取得
	Desktop_width_half = (Desktop_rect.right - Desktop_rect.left) / 2;
	//デスクトップ領域の高さの半分の値を取得
	Desktop_height_half = (Desktop_rect.bottom - Desktop_rect.top) / 2;

	//クライアント領域の幅の半分の値を取得
	Client_width_half = (rect_set.right - rect_set.left) / 2;
	//クライアント領域の高さの半分の値を取得
	Client_height_half = (rect_set.bottom - rect_set.top) / 2;

	//デスクトップの中央(横)を計算
	rect_set.left = Desktop_width_half - Client_width_half;
	//デスクトップの中央(縦)を計算
	rect_set.top = Desktop_height_half - Client_height_half;

	//クライアント領域の場所とサイズを再設定
	SetWindowPos(
		MyWin.hwnd,				//ウィンドウハンドル
		HWND_TOP,				//ウィンドウを前の面にする
		rect_set.left,			//ウィンドウのX座標
		rect_set.top,			//ウィンドウのY座標
		rect_set.right,			//ウィンドウの幅
		rect_set.bottom,		//ウィンドウの高さ
		SWP_SHOWWINDOW);		//ウィンドウを表示

	//調整したウィンドウ領域を取得
	GetWindowRect(MyWin.hwnd, &MyWin.win_rect_win);

	//調整したクライアント領域を取得
	GetClientRect(MyWin.hwnd, &MyWin.win_rect_cli);

	return;
}

///########## ダブルバッファリングの設定をする関数 ##########
//引　数：なし
//戻り値：なし
VOID MY_SetDoubleBufferring(VOID)
{
	// ウインドウのデバイスコンテキストのハンドルを取得
	HDC hdc = GetDC(MyWin.hwnd);

	//メモリの中にデバイスコンテキストのハンドルを作成
	MyWin.hdc_double = CreateCompatibleDC(hdc);

	//メモリの中に画像を作成
	MyWin.hbmp_double = CreateCompatibleBitmap(
		hdc,
		MyWin.win_rect_cli.right,
		MyWin.win_rect_cli.bottom);

	//デバイスコンテキストに画像を設定
	SelectObject(MyWin.hdc_double, MyWin.hbmp_double);

	return;
}