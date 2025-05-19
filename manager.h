//==================================================================
//
//マネージャー処理 [manager.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _MANAGER_H_					//このマクロ定義がされてなかったら
#define _MANAGER_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"
#include "input.h"

//================================================
//ライブラリのリンク
//================================================

//================================================
//マクロ定義
//================================================

//================================================
//クラス
//================================================
class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HWND hWnd,
		BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRenderer* GetRenderer(void);
	static CInputKeyboard* GetInputKeyboard(void);

private:
	static CRenderer* m_pRenderer;
	static CInputKeyboard* m_pInputKeyboard;
};

#endif