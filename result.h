//==================================================================
//
//シーン処理 [scene.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _RESULT_H_					//このマクロ定義がされてなかったら
#define _RESULT_H_					//2重インクルード防止のマクロ定義

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
#include "time.h"
#include "score.h"
//================================================
//マクロ定義
//================================================

//================================================
//クラス
//================================================
class CResult :public CScene
{
public:

	CResult();
	~CResult();

	virtual HRESULT Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	static CResult* Create();//生成処理

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
	static CScore* m_pScore;
};


#endif