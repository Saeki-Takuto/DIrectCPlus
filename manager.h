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
#include "object3D.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "debugproc.h"
#include "camera.h"
#include "light.h"

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
	static CPlayer* GetPlayer(void);
	static CCamera* GetCamera(void);
	static CLight* GetLight(void);


private:
	static CRenderer* m_pRenderer;
	static CInputKeyboard* m_pInputKeyboard;
	static CPlayer* m_pPlayer;
	static CCamera* m_pCamera;
	static CLight* m_pLight;
};

#endif