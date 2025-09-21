//==================================================================
//
//シーン処理 [scene.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _SCENE_H_					//このマクロ定義がされてなかったら
#define _SCENE_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "main.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラス
//================================================
class CScene
{
public:
	typedef enum
	{
		MODE_NONE = 0,
		MODE_TITLE,
		MODE_GAME,
		MODE_RESULT,
		MODE_TUTORIAL,
		MODE_TEMPLATE,
		MODE_MAX
	}MODE;

	CScene();
	~CScene();

	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	static CScene* Create(MODE mode);

	MODE GetMode() { return m_mode; }//現在のモード
	void SetMode(MODE mode) { m_mode = mode; }//モード

private:
	static MODE m_mode;
};


#endif