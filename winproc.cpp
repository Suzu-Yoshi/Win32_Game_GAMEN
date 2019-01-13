///▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
//winproc.cpp
///▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

///########## ヘッダファイル読み込み ##########
#include "main.h"
#include "fps.h"
#include "winproc.h"
#include "game.h"

///########## ライブラリ読み込み ##########

///########## マクロ定義 ##########

///########## 列挙型 ##########

///########## 構造体 ##########

///########## 名前の再定義 ##########

///########## グローバル変数の宣言と初期化 ##########

///########## プロトタイプ宣言 ##########

//ウィンドウプロシージャ
LRESULT CALLBACK MY_WndProc(HWND, UINT, WPARAM, LPARAM);

///########## ウィンドウプロシージャ関数 ##########
//引　数：メッセージが発生したときのインスタンスハンドル
//引　数：メッセージ
//引　数：付加情報１
//引　数：付加情報２
//戻り値：ウィンドウプロシージャから返される値
LRESULT CALLBACK MY_WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	//HDC：デバイスコンテキストのハンドル
	HDC hdc;

	//PAINTSTRUCT：ウィンドウごとの描画情報を管理する構造体
	PAINTSTRUCT ps;

	switch (msg)
	{

	case WM_CREATE:
		//ウィンドウの生成＆初期化

		///▼▼▼▼▼ ゲーム固有の設定ここから ▼▼▼▼▼


		///▲▲▲▲▲ ゲーム固有の設定ここまで ▲▲▲▲▲

		//ウィンドウを生成するときは、0を返す
		return 0;

	case WM_PAINT:
		//ウィンドウ内を再描画するとき

		//デバイスコンテキストのハンドルを取得
		hdc = BeginPaint(hwnd, &ps);

		//現在のデバイスコンテキストを保存する
		SaveDC(hdc);

		///▼▼▼▼▼ ゲーム固有の設定ここから ▼▼▼▼▼

		//画面の描画
		MY_DRAW_GAME(MyWin);

		//FPSの数値を描画
		MY_FPS_DRAW(MyWin.hdc_double);

		///▲▲▲▲▲ ゲーム固有の設定ここまで ▲▲▲▲▲

		//メモリ内の画像を描画
		BitBlt(hdc,
			0, 0, MyWin.win_rect_cli.right, MyWin.win_rect_cli.bottom,
			MyWin.hdc_double, 0, 0, SRCCOPY);

		//保存したデバイスコンテキスを復元する
		RestoreDC(hdc, -1);

		//デバイスコンテキストのハンドルを開放する
		EndPaint(hwnd, &ps);

		return 0;

	case WM_LBUTTONDOWN:
		//マウスの左ボタンを押しているとき

		//タイトルバーがないとき
		if (MyWin.win_mode == WIN_NO_TITLE)
		{
			//メッセージが送られる
			PostMessage(
				hwnd,				//ウィンドウハンドル
				WM_NCLBUTTONDOWN,	//非クライアント領域を左クリックする
				HTCAPTION,			//タイトルバーをクリックする
				MAKELPARAM(0, 0));	//マウスの座標：0,0

			return 0;
		}

		//クライアント領域外でもマウスの動きの監視を開始
		SetCapture(hwnd);

		break;

	case WM_LBUTTONUP:
		//マウスの左ボタンを上げたとき

		//タイトルバーがないとき
		if (MyWin.win_mode == WIN_NO_TITLE)
		{
			return 0;
		}

		//クライアント領域外でもマウスの動きの監視を終了
		ReleaseCapture();

		break;

	case WM_CLOSE:
		//閉じるボタンを押したとき

		break;
	case WM_DESTROY:
		//ウィンドウが破棄された(なくなった)とき

		///▼▼▼▼▼ ゲーム固有の設定ここから ▼▼▼▼▼


		///▲▲▲▲▲ ゲーム固有の設定ここまで ▲▲▲▲▲

		//メッセージキューに WM_QUIT を送る
		PostQuitMessage(0);

		return 0;
	}

	//デフォルトのウィンドウプロシージャ関数を呼び出す
	return DefWindowProc(hwnd, msg, wp, lp);
}