//==================================================================
//
//プレイヤー処理 [player.h]
//Author:Takuto Saeki
//
//==================================================================
#ifndef _PLAYER_H_					//このマクロ定義がされてなかったら
#define _PLAYER_H_					//2重インクルード防止のマクロ定義

//================================================
//インクルード
//================================================
#include "object2D.h"

//================================================
//マクロ定義
//================================================
#define PLAYER_PRIORITY (4)		//プレイヤーの優先度

//================================================
//クラス
//================================================
class CPlayer :public CObject2D
{
public:
    CPlayer(int nPriority);
	~CPlayer();

    static CPlayer* Create(
        DRAW_TYPE drawtype,
        int width,
        int height,
        float scrollX,
        float scrollY,
        int animeFrameU,
        int animeFrameV,
        int animePattern,
        float posX,
        float posY,
		float rotZ
    );
    HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

    static HRESULT Load(void);
	static void Unload(void);

	typedef struct
	{
	}Player;


private:
    static LPDIRECT3DTEXTURE9 m_pTexture;
	Player m_Player;
};

#endif