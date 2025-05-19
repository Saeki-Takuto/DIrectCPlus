//==================================================================
//
//入力処理 [input.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _INPUT_H_					//このマクロ定義がされてなかったら
#define _INPUT_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "d3dx9.h"
#include <dinput.h>

//================================================
//ライブラリのリンク
//================================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")											//入力処理に必要

//================================================
//マクロ定義
//================================================
#define DIRECTINPUT_VERSION (0x0800)//ビルドの警告対処用マクロ
#define NUM_KEY_MAX (256)

//================================================
//クラス
//================================================
class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//================================================
//キーボード入力クラス
//================================================
class CInputKeyboard :public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);

	bool Trigger(int nKey);
	bool Release(int nKey);
	bool Repeat(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aOldState[NUM_KEY_MAX];
};

#endif