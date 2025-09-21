//==================================================================
//
//シーン処理 [scene.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _TEMPLATESCENE_H_					//このマクロ定義がされてなかったら
#define _TEMPLATESCENE_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "main.h"
#include "scene.h"
#include "player.h"
#include "wall.h"
#include "rock.h"
#include "3Dplayer.h"
#include "background.h"
#include "object2D.h"
//================================================
//マクロ定義
//================================================

//================================================
//クラス
//================================================
class CTemplateScene :public CScene
{
public:

	CTemplateScene();
	~CTemplateScene();

	virtual HRESULT Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	static CTemplateScene* Create();//生成処理

	//static CPlayer* GetPlayer(void);
	static CWall* GetWall(void);
	static CRock* GetRock(void);
	static C3DPlayer* Get3DPlayer(void);

private:

	//static CPlayer* m_pPlayer;
	static C3DPlayer* m_p3DPlayer;
	static CWall* m_pWall;
	static CRock* m_pRock;

	static CScene* m_pScene;
	static CBackground* m_pBackground;
	static CObject2D* m_pObject2D;
};


#endif