//==================================================================
//
//C++とDirectX [main.cpp]
//Author:Takuto Saeki
//
//==================================================================

//================================================
//インクルード
//================================================
#include "main.h"
#include "manager.h"

//================================================
//グローバル変数
//================================================

//================================================
//メイン関数
//================================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	CManager* pManager = NULL;

	DWORD dwCurrentTime;							//現在時刻
	DWORD dwExecLastTime;							//最後に処理した時刻

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),							//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,									//ウィンドウのスタイル
		WindowProc,									//ウィンドウプロシージャ
		0,											//0にする(通常は使用しない)
		0,											//0にする(通常は使用しない)
		hInstance,									//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),				//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),					//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),					//クライアント領域の背景色
		NULL,										//メニューバー
		CLASS_NAME,									//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)				//ファイルのアイコン
	};

	HWND hWnd;//ウィンドウハンドル(識別子)
	MSG msg;//メッセージを格納する変数

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	//画面サイズの構造体

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,						//拡張ウィンドウスタイル
		CLASS_NAME,									//ウィンドウクラスの名前
		WINDOW_NAME,								//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,						//ウィンドウスタイル
		CW_USEDEFAULT,								//ウィンドウの左上X座標
		CW_USEDEFAULT,								//ウィンドウの左上Y座標
		(rect.right - rect.top),					//ウィンドウの幅
		(rect.bottom - rect.top),					//ウィンドウの高さ
		NULL,										//親ウィンドウのハンドル
		NULL,										//メニューハンドルまたは小ウィンドウID
		hInstance,									//インスタンスハンドル
		NULL);										//ウィンドウ作成データ

	//マネージャの生成
	pManager = new CManager;

	//マネージャの初期化処理
	pManager->Init(hWnd, TRUE);

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;								//初期化する
	dwExecLastTime = timeGetTime();					//現在時刻を取得(保存)

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);						//ウィンドウの表示状態を設定
	UpdateWindow(hWnd);								//クライアント領域を更新


	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				TranslateMessage(&msg);				//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);				//ウィンドウプロシージャへメッセージを送出
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;		//処理開始の時刻[現在時刻]を保存
				//更新処理
				pManager->Update();

				//描画処理
				pManager->Draw();
			}
		}
	}

	//マネージャの破棄
	if (pManager != NULL)
	{
		//マネージャの終了処理
		pManager->Uninit();

		delete pManager;

		pManager = NULL;
	}

	//分解能を戻す
	timeEndPeriod(1);

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//ウィンドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:								//ウィンドウ破棄のメッセージ
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:								//キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:								//[Esc]キーが押された
			//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//規定の処理を返す
}