///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//main.h
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## ヘッダファイル読み込み ##########
#include <windows.h>

///########## マクロ定義 ##########

//エラーメッセージ
#define ERR_MSG_TITLE			TEXT("WINDOW_ERROR")

#define ERR_MSG_NO_WIN_CLASS	TEXT("ウィンドウクラスが\
登録できませんでした\nプログラムを終了します")

#define ERR_MSG_NO_WIN_CREATE	TEXT("ウィンドウ\
が作成できませんでした\nプログラムを終了します")

//自分で作成するウィンドウクラスの名前
#define MY_WIN_CLASS	"MY_WIN_CLASS"

//ウィンドウのサイズを変更できなくする
#define WS_STATIC_WINDOW	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

//ウィンドウのタイトルをなくす
#define WS_NOT_TITLE WS_POPUP | WS_BORDER

//ゲームウィンドウの場所を大きさを設定
#define GAME_LEFT		0		//横の位置
#define GAME_TOP		0		//縦の位置
#define GAME_RIGHT		400		//幅
#define GAME_BOTTOM		400		//高さ
#define GAME_POS_X		  0		//左上のX座標
#define GAME_POS_Y		  0		//左上のY座標

//ゲームのタイトル
#define GAME_TITLE			"GAME_TITLE"

///########## 列挙型 ##########

//ウィンドウの表示を変更
enum WIN_MODE {
	WIN_RESZ_OK,	//0：ウィンドウサイズの変更ができる
	WIN_RESZ_NG,	//1：ウィンドウサイズの変更ができない
	WIN_NO_TITLE	//2：ウィンドウのタイトルをなくす
};

///########## 構造体 ##########

//自作ウィンドウ構造体
struct MY_STRUCT_GAME_WINDOW
{
	HWND		hwnd;			//ウィンドウハンドル(個々のウィンドウを識別)
	WNDCLASS	winc;			//ウィンドウクラスを管理
	MSG			msg;			//メッセージを保持
	RECT		win_size;		//ウィンドウの全体の場所と大きさを
	RECT		win_rect_win;	//ウインドウ領域	
	RECT		win_rect_cli;	//クライアント領域
	int			win_mode;		//ウィンドウの表示を設定
	HBITMAP		hbmp_double;	//ﾀﾞﾌﾞﾙﾊﾞｯﾌｧﾘﾝｸﾞ用
	HDC			hdc_double;		//ﾀﾞﾌﾞﾙﾊﾞｯﾌｧﾘﾝｸﾞ用
	POINT		point_Mouse;	//マウスの座標
};

///########## 名前の再定義 ##########
typedef MY_STRUCT_GAME_WINDOW	MY_WIN;

///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
#pragma once	//二重インクルードの防止
///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

///########## グローバル変数の宣言と初期化 ##########

///▼▼▼▼▼ 本体はmain.cpp ▼▼▼▼▼

//自作ウィンドウ構造体の変数
extern MY_WIN MyWin;

///▲▲▲▲▲ 本体はmain.cpp ▲▲▲▲▲

///########## 外部 関数 参照の宣言 ##########

///▼▼▼▼▼ 本体はmain.cpp ▼▼▼▼▼

//ウィンドウプロシージャ
extern LRESULT CALLBACK MY_WndProc(HWND, UINT, WPARAM, LPARAM);

//ウィンドウを生成する
extern BOOL MY_CreateWindowClass(HINSTANCE);

//自分のウィンドウクラスを作成、登録する関数
extern BOOL MY_CreateWindow(HINSTANCE);

//クライアント領域を設定する
extern VOID MY_SetClientSize(VOID);

//ダブルバッファリングの設定をする
extern VOID MY_SetDoubleBufferring(VOID);

///▲▲▲▲▲ 本体はmain.cpp ▲▲▲▲▲
